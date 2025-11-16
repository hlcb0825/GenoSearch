/*
 * automaton_logic.cpp (Corrected)
 * This file contains all the PURE C++ logic functions.
 * It implements the functions defined in automaton_logic.h.
 */

#include "automaton_logic.h" // Our engine's "menu"
#include "Automaton.h"       // Our engine's "parts"

#include <queue>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <chrono>
#include <cstdlib>

 // We wrap all our logic in the namespace
namespace GenoSearchEngine {

    // --- Internal Helper Function Prototypes ---
    std::string readFile(const std::string& filepath);
    void printHeader(std::stringstream& ss, const std::string& title);

    // Branch 1 Helpers
    int precedence(char op);
    std::string infixToPostfix(const std::string& infix);
    std::unique_ptr<NFA> buildThompson(const std::string& postfix, std::stringstream& grammar_ss);
    std::set<State*> epsilonClosure(std::set<State*>& states);
    std::set<State*> move(std::set<State*>& states, char input);
    std::unique_ptr<DFA> buildDFA(NFA* nfa);
    std::vector<std::string> simulateDFA(DFA* dfa, const std::string& text);
    std::string generateNfaDot(NFA* nfa);
    std::string generateDfaDot(DFA* dfa);
    std::string generateNfaGrammar(NFA* nfa); // Simplified

    // Branch 2A Helpers
    std::unique_ptr<NFA> buildSimpleNFA(const std::string& pattern, std::stringstream& grammar_ss);
    void fuzzySearch(const std::string& text, size_t text_idx, const std::string& pattern, size_t pattern_idx, int k_remaining, std::string current_match, std::set<std::pair<std::string, int>>& matches, int errors_made);

    // Branch 2B Helpers
    bool runPDASimulation(PDA* pda, const std::string& input);
    std::string getFileLines(const std::string& file_content, int max_lines = 10);
    std::string generateCFG();

    // Graphviz Fallback
    std::string GetTextFallback(const std::string& dot_string);


    // === UTILITY IMPLEMENTATION ===

    std::string readFile(const std::string& filepath) {
        std::ifstream file(filepath);
        if (!file.is_open()) {
            std::stringstream error_ss;
            error_ss << "[Error] Could not open file: " << filepath << "\n"
                << "Please check the file path and permissions.";
            return error_ss.str();
        }
        std::stringstream buffer;
        buffer << file.rdbuf();
        file.close();
        return buffer.str();
    }

    // Helper to get first few lines of a file (for PDA file mode)
    std::string getFileLines(const std::string& file_content, int max_lines) {
        std::stringstream ss(file_content);
        std::string line;
        std::stringstream out_ss;
        int count = 0;
        while (std::getline(ss, line) && count < max_lines) {
            // Remove carriage returns for cleaner output
            line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());
            out_ss << line << "\n";
            count++;
        }
        if (count >= max_lines) {
            out_ss << "...\n(and more lines)";
        }
        return out_ss.str();
    }


    void printHeader(std::stringstream& ss, const std::string& title) {
        ss << "--- " << title << " ---" << "\r\n";
    }

    // === BRANCH 1: REGEX ENGINE ===

    int precedence(char op) {
        if (op == '*') return 3;
        if (op == '.') return 2;
        if (op == '|') return 1;
        return 0;
    }

    std::string infixToPostfix(const std::string& infix) {
        std::string formattedInfix;
        for (size_t i = 0; i < infix.length(); ++i) {
            char c = infix[i];
            formattedInfix += c;
            if (i + 1 < infix.length()) {
                char next = infix[i + 1];
                if ((std::isalnum(c) || c == ')' || c == '*') &&
                    (std::isalnum(next) || next == '(')) {
                    formattedInfix += '.';
                }
            }
        }

        std::string postfix;
        std::stack<char> opStack;
        for (size_t i = 0; i < formattedInfix.length(); ++i) {
            char c = formattedInfix[i];
            if (std::isalnum(c)) {
                postfix += c;
            }
            else if (c == '(') {
                opStack.push(c);
            }
            else if (c == ')') {
                while (!opStack.empty() && opStack.top() != '(') {
                    postfix += opStack.top();
                    opStack.pop();
                }
                if (!opStack.empty()) opStack.pop();
            }
            else {
                while (!opStack.empty() && opStack.top() != '(' && precedence(opStack.top()) >= precedence(c)) {
                    postfix += opStack.top();
                    opStack.pop();
                }
                opStack.push(c);
            }
        }
        while (!opStack.empty()) {
            postfix += opStack.top();
            opStack.pop();
        }
        return postfix;
    }

    std::unique_ptr<NFA> buildThompson(const std::string& postfix, std::stringstream& grammar_ss) {
        std::stack<std::unique_ptr<NFA>> nfaStack;
        g_stateIdCounter = 0;
        int nonTerminalCounter = 0;

        grammar_ss << "(For: " << postfix << ")\r\n";

        // This is a placeholder grammar generator. A true
        // NFA->Grammar algorithm is complex.
        char NonTerminal = 'S';
        char nextNonTerminal = 'A';

        for (size_t i = 0; i < postfix.length(); ++i) {
            char c = postfix[i];
            if (std::isalnum(c)) {
                std::unique_ptr<NFA> nfa(new NFA());
                State* start = nfa->startState;
                State* accept = nfa->newState();
                start->addTransition(c, accept);
                accept->isAccepting = true;
                nfaStack.push(std::move(nfa));
                grammar_ss << NonTerminal << " -> " << c << nextNonTerminal << "\r\n";
                NonTerminal = nextNonTerminal++;
            }
            else if (c == '*') {
                grammar_ss << NonTerminal << " -> " << NonTerminal << NonTerminal << " | E (final)\r\n";
                std::unique_ptr<NFA> subNFA = std::move(nfaStack.top()); nfaStack.pop();
                std::unique_ptr<NFA> nfa(new NFA());
                State* start = nfa->startState;
                State* accept = nfa->newState();
                accept->isAccepting = true;

                State* oldAccept = NULL;
                for (size_t j = 0; j < subNFA->allStates.size(); ++j) {
                    if (subNFA->allStates[j]->isAccepting) {
                        oldAccept = subNFA->allStates[j];
                        break;
                    }
                }
                oldAccept->isAccepting = false;

                start->addTransition(EPSILON, subNFA->startState);
                start->addTransition(EPSILON, accept);
                oldAccept->addTransition(EPSILON, subNFA->startState);
                oldAccept->addTransition(EPSILON, accept);

                nfa->allStates.insert(nfa->allStates.end(), subNFA->allStates.begin(), subNFA->allStates.end());
                subNFA->allStates.clear();
                nfaStack.push(std::move(nfa));
            }
            else if (c == '|') {
                grammar_ss << NonTerminal << " -> ... | ...\r\n";
                std::unique_ptr<NFA> nfaB = std::move(nfaStack.top()); nfaStack.pop();
                std::unique_ptr<NFA> nfaA = std::move(nfaStack.top()); nfaStack.pop();
                std::unique_ptr<NFA> nfa(new NFA());
                State* start = nfa->startState;
                State* accept = nfa->newState();
                accept->isAccepting = true;

                State* acceptA = NULL;
                for (size_t j = 0; j < nfaA->allStates.size(); ++j) if (nfaA->allStates[j]->isAccepting) { acceptA = nfaA->allStates[j]; break; }
                State* acceptB = NULL;
                for (size_t j = 0; j < nfaB->allStates.size(); ++j) if (nfaB->allStates[j]->isAccepting) { acceptB = nfaB->allStates[j]; break; }
                acceptA->isAccepting = false;
                acceptB->isAccepting = false;

                start->addTransition(EPSILON, nfaA->startState);
                start->addTransition(EPSILON, nfaB->startState);
                acceptA->addTransition(EPSILON, accept);
                acceptB->addTransition(EPSILON, accept);

                nfa->allStates.insert(nfa->allStates.end(), nfaA->allStates.begin(), nfaA->allStates.end());
                nfaA->allStates.clear();
                nfa->allStates.insert(nfa->allStates.end(), nfaB->allStates.begin(), nfaB->allStates.end());
                nfaB->allStates.clear();
                nfaStack.push(std::move(nfa));
            }
            else if (c == '.') {
                std::unique_ptr<NFA> nfaB = std::move(nfaStack.top()); nfaStack.pop();
                std::unique_ptr<NFA> nfaA = std::move(nfaStack.top()); nfaStack.pop();

                State* acceptA = NULL;
                for (size_t j = 0; j < nfaA->allStates.size(); ++j) if (nfaA->allStates[j]->isAccepting) { acceptA = nfaA->allStates[j]; break; }
                acceptA->isAccepting = false;

                acceptA->addTransition(EPSILON, nfaB->startState);

                nfaA->allStates.insert(nfaA->allStates.end(), nfaB->allStates.begin(), nfaB->allStates.end());
                nfaB->allStates.clear();
                nfaStack.push(std::move(nfaA));
            }
        }
        grammar_ss << NonTerminal << " -> E (final)\r\n"; // Epsilon
        return std::move(nfaStack.top());
    }

    std::set<State*> epsilonClosure(std::set<State*>& states) {
        std::set<State*> closure = states;
        std::stack<State*> stateStack;
        for (std::set<State*>::iterator it = states.begin(); it != states.end(); ++it) {
            stateStack.push(*it);
        }

        while (!stateStack.empty()) {
            State* s = stateStack.top();
            stateStack.pop();
            if (s->transitions.count(EPSILON)) {
                std::vector<State*>& nextStates = s->transitions[EPSILON];
                for (std::vector<State*>::iterator it = nextStates.begin(); it != nextStates.end(); ++it) {
                    State* next = *it;
                    if (closure.find(next) == closure.end()) {
                        closure.insert(next);
                        stateStack.push(next);
                    }
                }
            }
        }
        return closure;
    }

    std::set<State*> move(std::set<State*>& states, char input) {
        std::set<State*> movedStates;
        for (std::set<State*>::iterator it = states.begin(); it != states.end(); ++it) {
            State* s = *it;
            if (s->transitions.count(input)) {
                std::vector<State*>& nextStates = s->transitions[input];
                for (std::vector<State*>::iterator nextIt = nextStates.begin(); nextIt != nextStates.end(); ++nextIt) {
                    movedStates.insert(*nextIt);
                }
            }
        }
        return movedStates;
    }

    std::unique_ptr<DFA> buildDFA(NFA* nfa) {
        std::unique_ptr<DFA> dfa(new DFA());
        int nextDfaId = 0;
        std::map<std::set<State*>, int> dfaStateMap;
        std::queue<std::set<State*>> workQueue;

        std::set<char> alphabet;
        for (size_t i = 0; i < nfa->allStates.size(); ++i) {
            State* s = nfa->allStates[i];
            for (std::map<char, std::vector<State*> >::iterator it = s->transitions.begin(); it != s->transitions.end(); ++it) {
                if (it->first != EPSILON) alphabet.insert(it->first);
            }
        }

        std::set<State*> startNFAStates;
        startNFAStates.insert(nfa->startState);
        std::set<State*> startClosure = epsilonClosure(startNFAStates);

        dfa->startStateId = nextDfaId;
        dfaStateMap[startClosure] = nextDfaId++;
        dfa->dfaStateToNFAStates[dfa->startStateId] = startClosure;
        workQueue.push(startClosure);

        while (!workQueue.empty()) {
            std::set<State*> currentNFAStates = workQueue.front();
            workQueue.pop();
            int currentDFAId = dfaStateMap[currentNFAStates];

            for (std::set<State*>::iterator it = currentNFAStates.begin(); it != currentNFAStates.end(); ++it) {
                if ((*it)->isAccepting) {
                    dfa->acceptingStateIds.insert(currentDFAId);
                    break;
                }
            }

            for (std::set<char>::iterator it = alphabet.begin(); it != alphabet.end(); ++it) {
                char c = *it;
                std::set<State*> moved = move(currentNFAStates, c);
                if (moved.empty()) continue;
                std::set<State*> nextNFAStates = epsilonClosure(moved);
                if (nextNFAStates.empty()) continue;

                int nextDFAId;
                if (dfaStateMap.find(nextNFAStates) == dfaStateMap.end()) {
                    nextDFAId = nextDfaId++;
                    dfaStateMap[nextNFAStates] = nextDFAId;
                    dfa->dfaStateToNFAStates[nextDFAId] = nextNFAStates;
                    workQueue.push(nextNFAStates);
                }
                else {
                    nextDFAId = dfaStateMap[nextNFAStates];
                }
                dfa->transitions[currentDFAId][c] = nextDFAId;
            }
        }
        return dfa;
    }

    std::vector<std::string> simulateDFA(DFA* dfa, const std::string& text) {
        std::vector<std::string> matches;
        std::string currentMatch;

        for (size_t i = 0; i < text.length(); ++i) {
            int currentState = dfa->startStateId;
            currentMatch = "";
            for (size_t j = i; j < text.length(); ++j) {
                char c = text[j];
                if (dfa->transitions.count(currentState) && dfa->transitions[currentState].count(c)) {
                    currentState = dfa->transitions[currentState].at(c);
                    currentMatch += c;
                    if (dfa->acceptingStateIds.count(currentState)) {
                        matches.push_back(currentMatch);
                    }
                }
                else {
                    break;
                }
            }
        }
        // Remove duplicate substrings
        if (!matches.empty()) {
            std::set<std::string> s(matches.begin(), matches.end());
            matches.assign(s.begin(), s.end());
        }
        return matches;
    }

    std::string generateNfaDot(NFA* nfa) {
        std::stringstream dot_ss;
        dot_ss << "digraph NFA {\n";
        dot_ss << "  rankdir=LR;\n";
        dot_ss << "  node [shape=circle, fontname=\"Consolas\"];\n";
        dot_ss << "  edge [fontname=\"Consolas\"];\n";
        dot_ss << "  start_node [shape=point, style=invis];\n";
        dot_ss << "  start_node -> q" << nfa->startState->id << ";\n";

        for (size_t i = 0; i < nfa->allStates.size(); ++i) {
            State* s = nfa->allStates[i];
            if (s->isAccepting) {
                dot_ss << "  q" << s->id << " [shape=doublecircle];\n";
            }
            for (std::map<char, std::vector<State*> >::iterator it = s->transitions.begin(); it != s->transitions.end(); ++it) {
                char key = it->first;
                std::vector<State*>& val = it->second;
                for (size_t j = 0; j < val.size(); ++j) {
                    State* next = val[j];
                    std::string label = (key == EPSILON) ? "\u03B5" : std::string(1, key); // Epsilon
                    dot_ss << "  q" << s->id << " -> q" << next->id << " [ label=\"" << label << "\" ];\n";
                }
            }
        }
        dot_ss << "}\n";
        return dot_ss.str();
    }

    std::string generateDfaDot(DFA* dfa) {
        std::stringstream dot_ss;
        dot_ss << "digraph DFA {\n";
        dot_ss << "  rankdir=LR;\n";
        dot_ss << "  node [shape=circle, fontname=\"Consolas\"];\n";
        dot_ss << "  edge [fontname=\"Consolas\"];\n";
        dot_ss << "  start_node [shape=point, style=invis];\n";
        dot_ss << "  start_node -> q" << dfa->startStateId << ";\n";

        for (std::set<int>::iterator it = dfa->acceptingStateIds.begin(); it != dfa->acceptingStateIds.end(); ++it) {
            dot_ss << "  q" << *it << " [shape=doublecircle];\n";
        }
        for (std::map<int, std::map<char, int> >::iterator it = dfa->transitions.begin(); it != dfa->transitions.end(); ++it) {
            int from = it->first;
            std::map<char, int>& table = it->second;
            for (std::map<char, int>::iterator it2 = table.begin(); it2 != table.end(); ++it2) {
                char input = it2->first;
                int to = it2->second;
                dot_ss << "  q" << from << " -> q" << to << " [ label=\"" << input << "\" ];\n";
            }
        }
        dot_ss << "}\n";
        return dot_ss.str();
    }

    std::string generateNfaGrammar(NFA* nfa) {
        // This is a placeholder. A real NFA->Grammar algorithm is complex.
        std::stringstream ss;
        ss << "(Grammar generation from a general NFA is complex.\r\n";
        ss << " A simple sequential grammar is shown instead.)\r\n";
        ss << "S -> ...\r\n";
        return ss.str();
    }


    // === BRANCH 2A: APPROXIMATE MATCH ===

    std::unique_ptr<NFA> buildSimpleNFA(const std::string& pattern, std::stringstream& grammar_ss) {
        g_stateIdCounter = 0;
        std::unique_ptr<NFA> nfa(new NFA());
        State* currentState = nfa->startState;

        grammar_ss << "(For exact pattern '" << pattern << "')\r\n";
        char NonTerminal = 'S';

        for (size_t i = 0; i < pattern.length(); ++i) {
            char c = pattern[i];
            State* nextState = nfa->newState();
            currentState->addTransition(c, nextState);

            grammar_ss << NonTerminal << " -> " << c;
            if (i < pattern.length() - 1) {
                char nextNonTerminal = NonTerminal + 1;
                if (nextNonTerminal > 'Z') nextNonTerminal = 'X'; // Avoid non-alpha
                grammar_ss << nextNonTerminal << "\r\n";
                NonTerminal = nextNonTerminal;
            }
            else {
                grammar_ss << "A\r\n"; // Final transition
            }
            currentState = nextState;
        }
        currentState->isAccepting = true;
        grammar_ss << "A -> \u03B5 (final)\r\n"; // Epsilon
        return nfa;
    }

    // Recursive backtracking search for fuzzy matching
    void fuzzySearch(const std::string& text, size_t text_idx,
        const std::string& pattern, size_t pattern_idx,
        int k_remaining, std::string current_match,
        std::set<std::pair<std::string, int>>& matches, int errors_made) {

        // Base case: Pattern is fully matched
        if (pattern_idx == pattern.length()) {
            matches.insert(std::make_pair(current_match, errors_made));
            return;
        }

        // Base case: Text is fully consumed but pattern is not
        if (text_idx == text.length()) {
            // We can still match if we "delete" the rest of the pattern
            if (k_remaining > 0) {
                fuzzySearch(text, text_idx, pattern, pattern_idx + 1, k_remaining - 1, current_match, matches, errors_made + 1);
            }
            return;
        }

        char text_char = text[text_idx];
        char pattern_char = pattern[pattern_idx];

        // 1. Match
        if (text_char == pattern_char) {
            fuzzySearch(text, text_idx + 1, pattern, pattern_idx + 1, k_remaining, current_match + text_char, matches, errors_made);
        }

        // 2. Errors (if we still have k > 0)
        if (k_remaining > 0) {
            // 2a. Substitution (consume both, cost 1)
            fuzzySearch(text, text_idx + 1, pattern, pattern_idx + 1, k_remaining - 1, current_match + text_char, matches, errors_made + 1);

            // 2b. Deletion (from pattern) (consume text, not pattern, cost 1)
            fuzzySearch(text, text_idx + 1, pattern, pattern_idx, k_remaining - 1, current_match + text_char, matches, errors_made + 1);

            // 2c. Insertion (into pattern) (consume pattern, not text, cost 1)
            fuzzySearch(text, text_idx, pattern, pattern_idx + 1, k_remaining - 1, current_match, matches, errors_made + 1);
        }
    }

    // === BRANCH 2B: PDA ===

    bool runPDASimulation(PDA* pda, const std::string& input) {
        pda->viz_stream.str(""); // Clear the stream
        pda->viz_stream << std::left
            << std::setw(20) << "Input Read"
            << std::setw(20) << "Stack"
            << std::setw(20) << "Action" << "\r\n";
        pda->viz_stream << std::string(60, '-') << "\r\n";

        std::string stack_str = pda->getStackString();
        pda->viz_stream << std::setw(20) << "(start)"
            << std::setw(20) << stack_str
            << std::setw(20) << "Initial State" << "\r\n";

        for (size_t i = 0; i < input.length(); ++i) {
            char c = input[i];
            std::string action = "SKIP (Terminal)";

            if (c == '(' || c == '[' || c == '{') {
                pda->stack.push(c);
                action = "PUSH";
            }
            else if (std::isalnum(c)) {
                // It's a terminal symbol, skip it
                action = "SKIP (Terminal)";
            }
            else if (c == ')' || c == ']' || c == '}') {
                if (pda->stack.empty() || pda->stack.top() == pda->stackStartSymbol) {
                    pda->stack.push('E'); // Error state
                    action = "REJECT (Pop empty stack)";
                    pda->didAccept = false;
                    pda->viz_stream << std::setw(20) << std::string(1, c)
                        << std::setw(20) << pda->getStackString()
                        << std::setw(20) << action << "\r\n";
                    break;
                }

                char top = pda->stack.top();
                bool match = (c == ')' && top == '(') ||
                    (c == ']' && top == '[') ||
                    (c == '}' && top == '{');

                if (match) {
                    pda->stack.pop();
                    action = "POP (Match)";
                }
                else {
                    pda->stack.push('E'); // Error state
                    action = "REJECT (Mismatch)";
                    pda->didAccept = false;
                    pda->viz_stream << std::setw(20) << std::string(1, c)
                        << std::setw(20) << pda->getStackString()
                        << std::setw(20) << action << "\r\n";
                    break;
                }
            }

            pda->viz_stream << std::setw(20) << std::string(1, c)
                << std::setw(20) << pda->getStackString()
                << std::setw(20) << action << "\r\n";
        }

        // --- Final Check ---
        if (pda->stack.size() == 1 && pda->stack.top() == pda->stackStartSymbol) {
            pda->didAccept = true;
            pda->viz_stream << std::setw(20) << "(end)"
                << std::setw(20) << pda->getStackString()
                << std::setw(20) << "ACCEPT (Stack empty)" << "\r\n";
        }
        else {
            pda->didAccept = false;
            pda->viz_stream << std::setw(20) << "(end)"
                << std::setw(20) << pda->getStackString()
                << std::setw(20) << "REJECT (Stack not empty)" << "\r\n";
        }
        return pda->didAccept;
    }

    std::string generateCFG() {
        std::stringstream ss;
        printHeader(ss, "Context-Free Grammar (CFG)");
        ss << "(For simple balanced structures)\r\n";
        ss << "S -> (S) | [S] | {S}\r\n";
        ss << "S -> SS\r\n";
        ss << "S -> \u03B5 (final)\r\n"; // Epsilon
        return ss.str();
    }


    // === PUBLIC WRAPPER FUNCTIONS (Called by MyForm.h) ===

    void runBranch1_logic(
        const std::string& regex, const std::string& filepath,
        SimulationReport& out_report, VisualizationData& out_viz, std::string& out_error_msg)
    {
        try {
            auto start = std::chrono::high_resolution_clock::now();
            std::stringstream ss_summary, ss_grammar, ss_results;

            std::string text = readFile(filepath);
            if (text.rfind("[Error]", 0) == 0) {
                out_error_msg = text;
                return;
            }

            std::string postfix = infixToPostfix(regex);
            std::unique_ptr<NFA> nfa = buildThompson(postfix, ss_grammar);
            std::unique_ptr<DFA> dfa = buildDFA(nfa.get());
            std::vector<std::string> matches = simulateDFA(dfa.get(), text);

            auto stop = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

            out_viz.nfaDot = generateNfaDot(nfa.get());
            out_viz.dfaDot = generateDfaDot(dfa.get());

            printHeader(ss_summary, "Simulation Summary");
            ss_summary << "Input Pattern:    " << regex << "\r\n";
            ss_summary << "File:             " << filepath << "\r\n";
            ss_summary << "Automaton Used:   DFA (Optimized)\r\n";
            ss_summary << "Time Taken:       " << duration.count() / 1000.0 << "s\r\n\r\n";
            ss_summary << "NFA (Unoptimized):\r\n";
            ss_summary << "  States:       " << nfa->allStates.size() << "\r\n";
            ss_summary << "DFA (Optimized):\r\n";
            ss_summary << "  States:       " << dfa->dfaStateToNFAStates.size() << "\r\n";

            printHeader(ss_results, "Match Report");
            ss_results << "(" << matches.size() << " Matches Found)\r\n";
            for (size_t i = 0; i < matches.size(); ++i) {
                ss_results << i + 1 << ": " << matches[i] << "\r\n";
            }

            out_report.summary = ss_summary.str();
            out_report.grammar = ss_grammar.str();
            out_report.matches = ss_results.str();
        }
        catch (std::exception& e) {
            out_error_msg = "[C++ Engine Error]\n" + std::string(e.what());
        }
    }

    void runBranch2A_logic(
        const std::string& pattern, int k, const std::string& filepath,
        SimulationReport& out_report, VisualizationData& out_viz, std::string& out_error_msg)
    {
        try {
            auto start = std::chrono::high_resolution_clock::now();
            std::stringstream ss_summary, ss_grammar, ss_results;

            std::string text = readFile(filepath);
            if (text.rfind("[Error]", 0) == 0) {
                out_error_msg = text;
                return;
            }

            std::unique_ptr<NFA> nfa = buildSimpleNFA(pattern, ss_grammar);
            std::set<std::pair<std::string, int>> matches;
            for (size_t i = 0; i < text.length(); ++i) {
                fuzzySearch(text, i, pattern, 0, k, "", matches, 0);
            }

            auto stop = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

            out_viz.nfaDot = generateNfaDot(nfa.get());

            printHeader(ss_summary, "Simulation Summary");
            ss_summary << "Input Pattern:    \"" << pattern << "\"\r\n";
            ss_summary << "File:             " << filepath << "\r\n";
            ss_summary << "Automaton Used:   NFA (Backtracking)\r\n";
            ss_summary << "Errors Allowed (k): " << k << "\r\n";
            ss_summary << "Time Taken:       " << duration.count() / 1000.0 << "s\r\n\r\n";
            ss_summary << "NFA (for exact pattern):\r\n";
            ss_summary << "  States:       " << nfa->allStates.size() << "\r\n";
            ss_summary << "Matches Found:    " << matches.size() << "\r\n";

            printHeader(ss_results, "Match Report");
            ss_results << "(" << matches.size() << " Matches Found)\r\n";
            int count = 1;
            for (std::set<std::pair<std::string, int>>::iterator it = matches.begin(); it != matches.end(); ++it) {
                ss_results << count++ << ": " << it->first << " (" << it->second << " errors)\r\n";
            }

            out_report.summary = ss_summary.str();
            out_report.grammar = ss_grammar.str();
            out_report.matches = ss_results.str();
        }
        catch (std::exception& e) {
            out_error_msg = "[C++ Engine Error]\n" + std::string(e.what());
        }
    }

    void runBranch2B_logic(
        const std::string& input, bool isFile,
        SimulationReport& out_report, VisualizationData& out_viz, std::string& out_error_msg)
    {
        try {
            std::stringstream ss_results, ss_grammar, ss_pda_trace;
            std::string input_string = input;

            if (isFile) {
                input_string = readFile(input); // 'input' is the filepath
                if (input_string.rfind("[Error]", 0) == 0) {
                    out_error_msg = input_string;
                    return;
                }
                // Validate line by line for a file
                std::stringstream file_stream(input_string);
                std::string line;
                int line_num = 1;
                int valid_count = 0;

                printHeader(ss_results, "Validation Report");
                ss_results << "Mode: Validating File (" << input << ")\r\n\r\n";

                while (std::getline(file_stream, line)) {
                    line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());
                    if (line.empty()) continue;

                    PDA pda;
                    bool isValid = runPDASimulation(&pda, line);
                    if (isValid) {
                        ss_results << "[Line " << line_num << "] VALID: \"" << line << "\"\r\n";
                        valid_count++;
                    }
                    else {
                        ss_results << "[Line " << line_num << "] INVALID: \"" << line << "\"\r\n";
                    }

                    // Only show trace for the first line
                    if (line_num == 1) {
                        ss_pda_trace << pda.viz_stream.str();
                    }
                    line_num++;
                }
                ss_results << "\r\nSummary: " << valid_count << " / " << (line_num - 1) << " lines are valid.";
                out_viz.pdaTrace = ss_pda_trace.str();

            }
            else {
                // Just validate the single string
                printHeader(ss_results, "Validation Report");
                ss_results << "Input: \"" << input_string << "\"\r\n\r\n";

                ss_results << "[DFA/NFA ATTEMPT (Level 1 Machine)]\r\n";
                ss_results << "[!] FAILED: Regular languages are insufficient.\r\n";
                ss_results << "Reason: A DFA/NFA has no memory (stack)\r\n";
                ss_results << "and cannot match nested structures like '()'.\r\n\r\n";

                PDA pda;
                bool isValid = runPDASimulation(&pda, input_string);
                out_viz.pdaTrace = pda.viz_stream.str();

                ss_results << "[PDA VALIDATION (Level 2 Machine)]\r\n";
                if (isValid) {
                    ss_results << "[+] SUCCEEDED: The string is VALID.\r\n";
                }
                else {
                    ss_results << "[!] FAILED: The string is INVALID.\r\n";
                }
            }

            out_report.grammar = generateCFG();
            out_report.matches = ss_results.str();
            out_report.summary = ""; // No summary for PDA
        }
        catch (std::exception& e) {
            out_error_msg = "[C++ Engine Error]\n" + std::string(e.what());
        }
    }


    // === GRAPHVIZ & FALLBACK IMPLEMENTATION ===

    bool GenerateGraphvizImage(
        const std::string& dot_string,
        const std::string& image_path,
        std::string& out_error_message,
        std::string& out_fallback_text)
    {
        std::string dot_path = "temp_graph.dot";

        std::ofstream dot_file(dot_path);
        if (!dot_file.is_open()) {
            out_error_message = "Error: Could not write temporary .dot file.";
            return false;
        }
        dot_file << dot_string;
        dot_file.close();

        std::string command = "dot -Tpng " + dot_path + " -o " + image_path;
        int result = system(command.c_str());

        if (result != 0) {
            out_error_message = "Error: Graphviz 'dot' command failed.\n"
                "Please ensure Graphviz is installed and in your system's PATH.\n\n"
                "--- FALLBACK VISUALIZATION ---";
            out_fallback_text = GetTextFallback(dot_string);
            return false;
        }

        return true;
    }

    std::string GetTextFallback(const std::string& dot_string) {
        std::stringstream fallback_ss;
        std::stringstream input_ss(dot_string);
        std::string line;

        while (std::getline(input_ss, line)) {
            size_t pos = line.find("->");
            if (pos != std::string::npos) {
                // Found a transition
                std::string part1 = line.substr(0, pos);
                std::string part2 = line.substr(pos + 2);

                size_t label_pos = part2.find("label=\"");
                std::string label = "?";
                if (label_pos != std::string::npos) {
                    label_pos += 7; // Skip 'label="'
                    size_t label_end = part2.find("\"", label_pos);
                    label = part2.substr(label_pos, label_end - label_pos);
                    if (label == "E") label = "\u03B5";
                }

                size_t from_pos = part1.find_last_of("q");
                size_t to_pos = part2.find_last_of("q");
                if (from_pos == std::string::npos || to_pos == std::string::npos) continue;

                std::string from = part1.substr(from_pos);
                std::string to = part2.substr(to_pos, part2.find_first_of(" [") - to_pos);

                fallback_ss << "(" << from << ") --'" << label << "'--> (" << to << ")\r\n";
            }
            else if (line.find("shape=point") != std::string::npos) {
                fallback_ss << "(start_node) is start\r\n";
            }
            else if (line.find("shape=doublecircle") != std::string::npos) {
                size_t q_pos = line.find("q");
                std::string state = line.substr(q_pos, line.find_first_of(" [") - q_pos);
                fallback_ss << "(" << state << ") is an accepting state\r\n";
            }
        }
        return fallback_ss.str();
    }

} // End namespace GenoSearchEngine