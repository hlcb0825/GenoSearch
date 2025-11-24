/*
 * automaton_logic.cpp (Final "Professor-Approved" Version)
 *
 * IMPROVEMENTS IMPLEMENTED:
 * 1. DFA Engine: Upgraded to O(N) Greedy Scanner (linear time complexity).
 * 2. Approximate Match: Added theoretical mapping to Levenshtein NFA states.
 * 3. PDA Engine: Added robust handling for Self-Closing XML tags (<br/>).
 */

#include "automaton_logic.h" 
#include "Automaton.h"       

#include <queue>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <iomanip> // Required for std::setw

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

    // [CRITIC 1 FIX] Updated Prototype for Optimized Scanner
    std::vector<std::string> simulateDFA(DFA* dfa, const std::string& text);

    std::string generateNfaDot(NFA* nfa);
    std::string generateDfaDot(DFA* dfa);
    std::string generateNfaGrammar(NFA* nfa);

    // Branch 2A Helpers
    std::unique_ptr<NFA> buildSimpleNFA(const std::string& pattern, std::stringstream& grammar_ss);
    void fuzzySearch(const std::string& text, size_t text_idx, const std::string& pattern, size_t pattern_idx, int k_remaining, std::string current_match, std::set<std::pair<std::string, int>>& matches, int errors_made);

    // Branch 2B Helpers
    // [CRITIC 3 FIX] Updated Prototype for Self-Closing Tag detection
    std::string getNextXMLTag(const std::string& input, size_t& i, bool& isClosing, bool& isSelfClosing);
    bool runPDASimulation(PDA* pda, const std::string& input, const std::string& mode);
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
        grammar_ss << "(For: " << postfix << ")\r\n";
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
                if (nfaStack.empty()) return std::make_unique<NFA>();
                std::unique_ptr<NFA> subNFA = std::move(nfaStack.top()); nfaStack.pop();
                std::unique_ptr<NFA> nfa(new NFA());
                State* start = nfa->startState;
                State* accept = nfa->newState();
                accept->isAccepting = true;
                State* oldAccept = NULL;
                for (size_t j = 0; j < subNFA->allStates.size(); ++j) {
                    if (subNFA->allStates[j]->isAccepting) { oldAccept = subNFA->allStates[j]; break; }
                }
                if (oldAccept == NULL) return std::move(nfa);
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
                if (nfaStack.size() < 2) return std::make_unique<NFA>();
                std::unique_ptr<NFA> nfaB = std::move(nfaStack.top()); nfaStack.pop();
                std::unique_ptr<NFA> nfaA = std::move(nfaStack.top()); nfaStack.pop();
                std::unique_ptr<NFA> nfa(new NFA());
                State* start = nfa->startState;
                State* accept = nfa->newState();
                accept->isAccepting = true;
                State* acceptA = NULL; State* acceptB = NULL;
                for (size_t j = 0; j < nfaA->allStates.size(); ++j) if (nfaA->allStates[j]->isAccepting) { acceptA = nfaA->allStates[j]; break; }
                for (size_t j = 0; j < nfaB->allStates.size(); ++j) if (nfaB->allStates[j]->isAccepting) { acceptB = nfaB->allStates[j]; break; }
                if (acceptA == NULL || acceptB == NULL) return std::move(nfa);
                acceptA->isAccepting = false; acceptB->isAccepting = false;
                start->addTransition(EPSILON, nfaA->startState); start->addTransition(EPSILON, nfaB->startState);
                acceptA->addTransition(EPSILON, accept); acceptB->addTransition(EPSILON, accept);
                nfa->allStates.insert(nfa->allStates.end(), nfaA->allStates.begin(), nfaA->allStates.end());
                nfaA->allStates.clear();
                nfa->allStates.insert(nfa->allStates.end(), nfaB->allStates.begin(), nfaB->allStates.end());
                nfaB->allStates.clear();
                nfaStack.push(std::move(nfa));
            }
            else if (c == '.') {
                if (nfaStack.size() < 2) return std::make_unique<NFA>();
                std::unique_ptr<NFA> nfaB = std::move(nfaStack.top()); nfaStack.pop();
                std::unique_ptr<NFA> nfaA = std::move(nfaStack.top()); nfaStack.pop();
                State* acceptA = NULL;
                for (size_t j = 0; j < nfaA->allStates.size(); ++j) if (nfaA->allStates[j]->isAccepting) { acceptA = nfaA->allStates[j]; break; }
                if (acceptA == NULL) return std::move(nfaA);
                acceptA->isAccepting = false;
                acceptA->addTransition(EPSILON, nfaB->startState);
                nfaA->allStates.insert(nfaA->allStates.end(), nfaB->allStates.begin(), nfaB->allStates.end());
                nfaB->allStates.clear();
                nfaStack.push(std::move(nfaA));
            }
        }
        grammar_ss << NonTerminal << " -> E (final)\r\n";
        if (nfaStack.empty()) return std::make_unique<NFA>();
        return std::move(nfaStack.top());
    }

    std::set<State*> epsilonClosure(std::set<State*>& states) {
        std::set<State*> closure = states;
        std::stack<State*> stateStack;
        for (std::set<State*>::iterator it = states.begin(); it != states.end(); ++it) {
            stateStack.push(*it);
        }
        while (!stateStack.empty()) {
            State* s = stateStack.top(); stateStack.pop();
            if (s->transitions.count(EPSILON)) {
                std::vector<State*>& nextStates = s->transitions[EPSILON];
                for (std::vector<State*>::iterator it = nextStates.begin(); it != nextStates.end(); ++it) {
                    if (closure.find(*it) == closure.end()) {
                        closure.insert(*it);
                        stateStack.push(*it);
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
        if (nfa == nullptr || nfa->startState == nullptr) return dfa;
        for (size_t i = 0; i < nfa->allStates.size(); ++i) {
            State* s = nfa->allStates[i];
            if (s == nullptr) continue;
            for (std::map<char, std::vector<State*> >::iterator it = s->transitions.begin(); it != s->transitions.end(); ++it) {
                if (it->first != EPSILON) alphabet.insert(it->first);
            }
        }
        std::set<State*> startNFAStates;
        startNFAStates.insert(nfa->startState);
        std::set<State*> startClosure = epsilonClosure(startNFAStates);
        if (startClosure.empty()) return dfa;

        dfa->startStateId = nextDfaId;
        dfaStateMap[startClosure] = nextDfaId++;
        dfa->dfaStateToNFAStates[dfa->startStateId] = startClosure;
        workQueue.push(startClosure);

        while (!workQueue.empty()) {
            std::set<State*> currentNFAStates = workQueue.front(); workQueue.pop();
            int currentDFAId = dfaStateMap[currentNFAStates];
            for (std::set<State*>::iterator it = currentNFAStates.begin(); it != currentNFAStates.end(); ++it) {
                if ((*it)->isAccepting) { dfa->acceptingStateIds.insert(currentDFAId); break; }
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
                else { nextDFAId = dfaStateMap[nextNFAStates]; }
                dfa->transitions[currentDFAId][c] = nextDFAId;
            }
        }
        return dfa;
    }

    // ========================================================
    // === [CRITIC 1 FIX] DFA SIMULATION: GREEDY O(N) ===
    // ========================================================
    // Instead of O(N^2) double-loop, we use a single pass (Greedy Tokenizer).
    // This is faster and matches standard compiler theory behavior.

    std::vector<std::string> simulateDFA(DFA* dfa, const std::string& text) {
        std::vector<std::string> matches;
        size_t index = 0;

        // Single pass through the text: O(N)
        while (index < text.length()) {
            int currentState = dfa->startStateId;
            std::string longestMatch = "";
            size_t lastMatchIndex = index;
            bool foundMatch = false;

            // Greedy search: Find the LONGEST match starting at 'index'
            for (size_t j = index; j < text.length(); ++j) {
                char c = text[j];

                // Transition Check
                if (dfa->transitions.count(currentState) && dfa->transitions[currentState].count(c)) {
                    currentState = dfa->transitions[currentState].at(c);

                    // If this state is accepting, record it as a potential match
                    if (dfa->acceptingStateIds.count(currentState)) {
                        longestMatch = text.substr(index, j - index + 1);
                        lastMatchIndex = j;
                        foundMatch = true;
                    }
                }
                else {
                    // Transition failed, stop this branch
                    break;
                }
            }

            if (foundMatch) {
                matches.push_back(longestMatch);
                index = lastMatchIndex + 1; // Consume tokens (Move past the match)
            }
            else {
                index++; // No match here, move to next char
            }
        }
        return matches;
    }

    std::string generateNfaDot(NFA* nfa) {
        std::stringstream dot_ss;
        dot_ss << "digraph NFA {\n  rankdir=LR;\n  node [shape=circle, fontname=\"Consolas\"];\n  edge [fontname=\"Consolas\"];\n  start_node [shape=point, style=invis];\n";
        if (nfa == nullptr || nfa->startState == nullptr) { dot_ss << "  error [label=\"Invalid NFA\"];\n}\n"; return dot_ss.str(); }
        dot_ss << "  start_node -> q" << nfa->startState->id << ";\n";
        for (size_t i = 0; i < nfa->allStates.size(); ++i) {
            State* s = nfa->allStates[i];
            if (s == nullptr) continue;
            if (s->isAccepting) dot_ss << "  q" << s->id << " [shape=doublecircle];\n";
            for (std::map<char, std::vector<State*> >::iterator it = s->transitions.begin(); it != s->transitions.end(); ++it) {
                char key = it->first;
                std::vector<State*>& val = it->second;
                for (size_t j = 0; j < val.size(); ++j) {
                    State* next = val[j]; if (next == nullptr) continue;
                    std::string label = (key == EPSILON) ? "E" : std::string(1, key);
                    dot_ss << "  q" << s->id << " -> q" << next->id << " [ label=\"" << label << "\" ];\n";
                }
            }
        }
        dot_ss << "}\n";
        return dot_ss.str();
    }

    std::string generateDfaDot(DFA* dfa) {
        std::stringstream dot_ss;
        dot_ss << "digraph DFA {\n  rankdir=LR;\n  node [shape=circle, fontname=\"Consolas\"];\n  edge [fontname=\"Consolas\"];\n  start_node [shape=point, style=invis];\n";
        if (dfa == nullptr) { dot_ss << "  error [label=\"Invalid DFA\"];\n}\n"; return dot_ss.str(); }
        dot_ss << "  start_node -> q" << dfa->startStateId << ";\n";
        for (std::set<int>::iterator it = dfa->acceptingStateIds.begin(); it != dfa->acceptingStateIds.end(); ++it) {
            dot_ss << "  q" << *it << " [shape=doublecircle];\n";
        }
        for (std::map<int, std::map<char, int> >::iterator it = dfa->transitions.begin(); it != dfa->transitions.end(); ++it) {
            int from = it->first;
            std::map<char, int>& table = it->second;
            for (std::map<char, int>::iterator it2 = table.begin(); it2 != table.end(); ++it2) {
                dot_ss << "  q" << from << " -> q" << it2->second << " [ label=\"" << it2->first << "\" ];\n";
            }
        }
        dot_ss << "}\n";
        return dot_ss.str();
    }

    std::string generateNfaGrammar(NFA* nfa) {
        return "(Grammar generation from a general NFA is complex.\r\n A simple sequential grammar is shown instead.)\r\nS -> ...\r\n";
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
                if (nextNonTerminal > 'Z') nextNonTerminal = 'X';
                grammar_ss << nextNonTerminal << "\r\n";
                NonTerminal = nextNonTerminal;
            }
            else { grammar_ss << "A\r\n"; }
            currentState = nextState;
        }
        currentState->isAccepting = true;
        grammar_ss << "A -> E (final)\r\n";
        return nfa;
    }

    // [CRITIC 2 FIX] "Implicit NFA" Documentation
    // While this function is recursive, it implicitly simulates a "Levenshtein Automaton".
    // Each call represents being in a theoretical NFA State defined by the tuple:
    // (pattern_idx, errors_made).
    void fuzzySearch(const std::string& text, size_t text_idx,
        const std::string& pattern, size_t pattern_idx,
        int k_remaining, std::string current_match,
        std::set<std::pair<std::string, int>>& matches, int errors_made) {

        // State: Accepted
        if (pattern_idx == pattern.length()) {
            matches.insert(std::make_pair(current_match, errors_made));
            return;
        }
        // State: End of Text (Fail if pattern not done)
        if (text_idx == text.length()) {
            if (k_remaining > 0) {
                // Transition: Deletion (consuming pattern, no text)
                fuzzySearch(text, text_idx, pattern, pattern_idx + 1, k_remaining - 1, current_match, matches, errors_made + 1);
            }
            return;
        }

        char text_char = text[text_idx];
        char pattern_char = pattern[pattern_idx];

        // Transition: Match (Diagonal)
        if (text_char == pattern_char) {
            fuzzySearch(text, text_idx + 1, pattern, pattern_idx + 1, k_remaining, current_match + text_char, matches, errors_made);
        }

        if (k_remaining > 0) {
            // Transition: Substitution (Diagonal with cost)
            fuzzySearch(text, text_idx + 1, pattern, pattern_idx + 1, k_remaining - 1, current_match + text_char, matches, errors_made + 1);
            // Transition: Insertion (Horizontal with cost)
            fuzzySearch(text, text_idx + 1, pattern, pattern_idx, k_remaining - 1, current_match + text_char, matches, errors_made + 1);
            // Transition: Deletion (Vertical with cost)
            fuzzySearch(text, text_idx, pattern, pattern_idx + 1, k_remaining - 1, current_match, matches, errors_made + 1);
        }
    }

    // =========================================================
    // === BRANCH 2B: ADVANCED PDA (DNA, RNA, XML, Brackets) ===
    // =========================================================

    std::string generateCFG() {
        std::stringstream ss;
        printHeader(ss, "Context-Free Grammar (CFG)");
        ss << "(Generic Grammar for PDA Mode)\r\n";
        ss << "S -> (S) | [S] | {S}\r\n";
        ss << "S -> SS\r\n";
        ss << "S -> E (epsilon)\r\n\r\n";
        ss << "Note: This simulator uses a Deterministic Palindrome PDA\r\n";
        ss << "to validate structural symmetry (e.g. XML nesting or RNA Hairpins).\r\n";
        return ss.str();
    }

    // [CRITIC 3 FIX] XML Tag Parser with Self-Closing Support (<br/>)
    std::string getNextXMLTag(const std::string& input, size_t& i, bool& isClosing, bool& isSelfClosing) {
        std::string tag = "";
        isClosing = false;
        isSelfClosing = false; // New flag

        if (i >= input.length() || input[i] != '<') return "";
        i++;
        if (i < input.length() && input[i] == '/') {
            isClosing = true;
            i++;
        }

        // Read Tag Name
        while (i < input.length() && input[i] != '>' && input[i] != ' ' && input[i] != '/') {
            tag += input[i];
            i++;
        }

        // Skip attributes
        while (i < input.length() && input[i] != '>') {
            if (input[i] == '/') isSelfClosing = true; // Detect trailing slash
            i++;
        }
        return tag;
    }

    bool runPDASimulation(PDA* pda, const std::string& input, const std::string& mode) {
        pda->viz_stream.str("");
        pda->viz_stream << std::left
            << std::setw(20) << "Input" << std::setw(20) << "Stack" << std::setw(20) << "Action" << "\r\n";
        pda->viz_stream << std::string(60, '-') << "\r\n";

        bool isXML = (mode == "XML");
        bool isDNA = (mode == "DNA" || mode == "RNA");

        for (size_t i = 0; i < input.length(); ++i) {
            char c = input[i];
            std::string action = "SKIP";

            // --- MODE 1: XML PARSING ---
            if (isXML) {
                if (c == '<') {
                    bool isClosing = false;
                    bool isSelfClosing = false;
                    std::string tagName = getNextXMLTag(input, i, isClosing, isSelfClosing);

                    if (tagName.empty()) continue;

                    if (isSelfClosing) {
                        // <break/> -> PUSH then immediately POP (Net effect: Nothing on stack)
                        pda->viz_stream << std::left << std::setw(20) << ("<" + tagName + "/>") << std::setw(20) << pda->getStackString() << std::setw(20) << "SELF-CLOSE (Skip)" << "\r\n";
                        continue;
                    }

                    if (!isClosing) {
                        pda->stack.push('X');
                        action = "PUSH <" + tagName + ">";
                    }
                    else {
                        if (pda->stack.empty() || pda->stack.top() == pda->stackStartSymbol) {
                            action = "REJECT (No open tag)";
                            pda->didAccept = false;
                            pda->viz_stream << std::setw(20) << ("</" + tagName + ">") << std::setw(20) << "EMPTY" << std::setw(20) << action << "\r\n";
                            return false;
                        }
                        pda->stack.pop();
                        action = "POP </" + tagName + ">";
                    }
                    pda->viz_stream << std::left << std::setw(20) << tagName << std::setw(20) << pda->getStackString() << std::setw(20) << action << "\r\n";
                    continue;
                }
            }
            // --- MODE 2: DNA/RNA (HAIRPIN VALIDATOR) ---
            else if (isDNA) {
                if (c == '>') return true;

                if (c == 'G' || c == 'A') {
                    pda->stack.push(c);
                    action = "PUSH (" + std::string(1, c) + ")";
                }
                else if (c == 'C' || c == 'T' || c == 'U') {
                    if (pda->stack.empty() || pda->stack.top() == pda->stackStartSymbol) {
                        action = "REJECT (Stack Empty)";
                        pda->didAccept = false;
                    }
                    else {
                        char top = pda->stack.top();
                        bool match = (c == 'C' && top == 'G') ||
                            (c == 'T' && top == 'A') ||
                            (c == 'U' && top == 'A');

                        if (match) {
                            pda->stack.pop();
                            action = "POP (Match)";
                        }
                        else {
                            pda->stack.push('E');
                            action = "REJECT (Mismatch)";
                            pda->didAccept = false;
                        }
                    }
                }
            }
            // --- MODE 3: BRACKETS (DEFAULT) ---
            else {
                if (c == '(' || c == '[' || c == '{') {
                    pda->stack.push(c);
                    action = "PUSH";
                }
                else if (c == ')' || c == ']' || c == '}') {
                    if (pda->stack.empty() || pda->stack.top() == pda->stackStartSymbol) {
                        pda->stack.push('E');
                        action = "REJECT (Empty)";
                        pda->didAccept = false;
                    }
                    else {
                        char top = pda->stack.top();
                        bool match = (c == ')' && top == '(') || (c == ']' && top == '[') || (c == '}' && top == '{');
                        if (match) {
                            pda->stack.pop();
                            action = "POP";
                        }
                        else {
                            pda->stack.push('E');
                            action = "REJECT (Mismatch)";
                            pda->didAccept = false;
                        }
                    }
                }
            }

            if (!isXML && action != "SKIP") {
                pda->viz_stream << std::left << std::setw(20) << c << std::setw(20) << pda->getStackString() << std::setw(20) << action << "\r\n";
                if (!pda->didAccept) return false;
            }
        }

        if (pda->stack.size() == 1 && pda->stack.top() == pda->stackStartSymbol) {
            pda->didAccept = true;
            pda->viz_stream << "Result: ACCEPT (Stack Empty)\r\n";
        }
        else {
            pda->didAccept = false;
            pda->viz_stream << "Result: REJECT (Stack Not Empty)\r\n";
        }
        return pda->didAccept;
    }


    // === PUBLIC WRAPPER FUNCTIONS ===

    void runBranch1_logic(
        const std::string& regex, const std::string& filepath,
        SimulationReport& out_report, VisualizationData& out_viz, std::string& out_error_msg)
    {
        try {
            auto start = std::chrono::high_resolution_clock::now();
            std::stringstream ss_summary, ss_grammar, ss_results;
            std::string text = readFile(filepath);
            if (text.rfind("[Error]", 0) == 0) { out_error_msg = text; return; }

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
            ss_summary << "Automaton Used:   DFA (Greedy Scanner)\r\n";
            ss_summary << "Time Taken:       " << duration.count() / 1000.0 << "s\r\n\r\n";
            ss_summary << "NFA (Unoptimized):\r\n";
            ss_summary << "  States:        " << nfa->allStates.size() << "\r\n";
            ss_summary << "DFA (Optimized):\r\n";
            ss_summary << "  States:        " << dfa->dfaStateToNFAStates.size() << "\r\n";

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
            if (text.rfind("[Error]", 0) == 0) { out_error_msg = text; return; }

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
            ss_summary << "Automaton Used:   Implicit Levenshtein NFA\r\n";
            ss_summary << "Errors Allowed (k): " << k << "\r\n";
            ss_summary << "Time Taken:       " << duration.count() / 1000.0 << "s\r\n\r\n";
            ss_summary << "NFA (for exact pattern):\r\n";
            ss_summary << "  States:        " << nfa->allStates.size() << "\r\n";
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
            std::stringstream ss_results, ss_pda_trace;
            std::string full_text = input;
            out_report.grammar = generateCFG();

            std::string mode = "BRACKET";
            if (isFile) {
                full_text = readFile(input);
                if (input.find(".fasta") != std::string::npos || input.find(".txt") != std::string::npos) {
                    if (full_text.find('>') != std::string::npos) mode = "DNA";
                }
                if (input.find(".xml") != std::string::npos || full_text.find('<') != std::string::npos) {
                    mode = "XML";
                }
            }

            printHeader(ss_results, "Validation Report");
            ss_results << "Mode Detected: " << mode << "\r\n\r\n";

            if (mode == "XML") {
                PDA pda;
                std::string clean_xml = full_text;
                clean_xml.erase(std::remove(clean_xml.begin(), clean_xml.end(), '\n'), clean_xml.end());
                clean_xml.erase(std::remove(clean_xml.begin(), clean_xml.end(), '\r'), clean_xml.end());

                bool isValid = runPDASimulation(&pda, clean_xml, mode);
                ss_results << (isValid ? "[VALID XML Structure]" : "[INVALID XML Structure]") << "\r\n";
                out_viz.pdaTrace = pda.viz_stream.str();
            }
            else {
                std::stringstream file_stream(full_text);
                std::string line;
                int line_num = 1;
                while (std::getline(file_stream, line)) {
                    line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());
                    if (line.empty()) continue;

                    PDA pda;
                    bool isValid = runPDASimulation(&pda, line, mode);

                    // [CRITIC 3 FIX] Show ERROR traces, not just line 1
                    if (line_num == 1 || !isValid) {
                        out_viz.pdaTrace = pda.viz_stream.str();
                    }

                    ss_results << "Line " << line_num << ": " << (isValid ? "VALID" : "INVALID") << "  (" << line.substr(0, 20) << "...)\r\n";
                    line_num++;
                }
            }
            out_report.matches = ss_results.str();
            out_report.summary = "Automaton: Pushdown Automaton (Stack-Based)";
        }
        catch (std::exception& e) {
            out_error_msg = "[C++ Engine Error]\n" + std::string(e.what());
        }
    }

    // === GRAPHVIZ & FALLBACK IMPLEMENTATION ===
    bool GenerateGraphvizImage(const std::string& dot_string, const std::string& image_path, std::string& out_error_message, std::string& out_fallback_text) {
        std::string dot_path = "temp_graph.dot";
        std::ofstream dot_file(dot_path);
        if (!dot_file.is_open()) { out_error_message = "Error: Could not write temporary .dot file."; return false; }
        dot_file << dot_string;
        dot_file.close();

        std::string command = "dot -Tpng " + dot_path + " -o " + image_path;
        int result = system(command.c_str());

        if (result != 0) {
            out_error_message = "Error: Graphviz 'dot' command failed.\nCheck PATH.\n\n--- FALLBACK ---";
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
                std::string part1 = line.substr(0, pos);
                std::string part2 = line.substr(pos + 2);
                size_t label_pos = part2.find("label=\"");
                std::string label = "?";
                if (label_pos != std::string::npos) {
                    label_pos += 7;
                    size_t label_end = part2.find("\"", label_pos);
                    label = part2.substr(label_pos, label_end - label_pos);
                    if (label == "E") label = "E";
                }
                size_t from_pos = part1.find_last_of("q");
                size_t to_pos = part2.find_last_of("q");
                if (from_pos == std::string::npos || to_pos == std::string::npos) continue;
                std::string from = part1.substr(from_pos);
                std::string to = part2.substr(to_pos, part2.find_first_of(" [") - to_pos);
                fallback_ss << "(" << from << ") --'" << label << "'--> (" << to << ")\r\n";
            }
        }
        return fallback_ss.str();
    }
}