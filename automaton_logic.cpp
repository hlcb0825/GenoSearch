#include "automaton_logic.h" 
#include "Automaton.h"       

#include <queue>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <iomanip>
#include <set>
#include <map>
#include <vector>
#include <stack>

int g_stateIdCounter = 0;

namespace GenoSearchEngine {

    // ========================================
    // ESCAPE SEQUENCE TOKENS
    // ========================================

    const char ESCAPED_DOT = 0x01;
    const char ESCAPED_STAR = 0x02;
    const char ESCAPED_PIPE = 0x03;
    const char ESCAPED_LPAREN = 0x04;
    const char ESCAPED_RPAREN = 0x05;
    const char ESCAPED_BACKSLASH = 0x06;

    static char mapEscapeSequence(char escapedChar) {
        switch (escapedChar) {
        case '.': return ESCAPED_DOT;
        case '*': return ESCAPED_STAR;
        case '|': return ESCAPED_PIPE;
        case '(': return ESCAPED_LPAREN;
        case ')': return ESCAPED_RPAREN;
        case '\\': return ESCAPED_BACKSLASH;
        default: return escapedChar;
        }
    }

    static char unmapEscapeToken(char token) {
        switch (token) {
        case ESCAPED_DOT: return '.';
        case ESCAPED_STAR: return '*';
        case ESCAPED_PIPE: return '|';
        case ESCAPED_LPAREN: return '(';
        case ESCAPED_RPAREN: return ')';
        case ESCAPED_BACKSLASH: return '\\';
        default: return token;
        }
    }

    static bool isEscapeToken(char c) {
        return (c >= 0x01 && c <= 0x06);
    }

    // ========================================
    // UTILITY FUNCTIONS
    // ========================================

    std::string readFile(const std::string& filepath) {
        std::ifstream file(filepath);
        if (!file.is_open()) {
            std::stringstream error_ss;
            error_ss << "[Error] Could not open file: " << filepath << "\n";
            return error_ss.str();
        }
        std::stringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    }

    void printHeader(std::stringstream& ss, const std::string& title) {
        ss << "\n=== " << title << " ===\n";
    }

    // ========================================
    // REGEX ENGINE (WITH ESCAPE SUPPORT)
    // ========================================

    int precedence(char op) {
        if (op == '*') return 3;
        if (op == '.') return 2;
        if (op == '|') return 1;
        return 0;
    }

    std::string infixToPostfix(const std::string& infix) {
        // PASS 1: Handle escape sequences
        std::string processed;
        bool escapeNext = false;

        for (size_t i = 0; i < infix.length(); ++i) {
            char c = infix[i];
            if (escapeNext) {
                processed += mapEscapeSequence(c);
                escapeNext = false;
            }
            else if (c == '\\') {
                escapeNext = true;
            }
            else {
                processed += c;
            }
        }

        // PASS 2: Insert concatenation operators
        std::string formattedInfix;
        for (size_t i = 0; i < processed.length(); ++i) {
            char c = processed[i];
            formattedInfix += c;

            if (i + 1 < processed.length()) {
                char next = processed[i + 1];
                bool currentIsLiteral = std::isalnum(c) || isEscapeToken(c) || c == ')' || c == '*';
                bool nextIsLiteral = std::isalnum(next) || isEscapeToken(next) || next == '(';

                if (currentIsLiteral && nextIsLiteral) {
                    formattedInfix += '.';
                }
            }
        }

        // PASS 3: Shunting Yard
        std::string postfix;
        std::stack<char> opStack;

        for (size_t i = 0; i < formattedInfix.length(); ++i) {
            char c = formattedInfix[i];

            if (std::isalnum(c) || isEscapeToken(c)) {
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
                while (!opStack.empty() && opStack.top() != '(' &&
                    precedence(opStack.top()) >= precedence(c)) {
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

        for (size_t i = 0; i < postfix.length(); ++i) {
            char c = postfix[i];

            if (std::isalnum(c) || isEscapeToken(c)) {
                std::unique_ptr<NFA> nfa(new NFA());
                State* start = nfa->startState;
                State* accept = nfa->newState();

                char transitionChar = isEscapeToken(c) ? unmapEscapeToken(c) : c;
                start->addTransition(transitionChar, accept);
                accept->isAccepting = true;
                nfaStack.push(std::move(nfa));
            }
            else if (c == '*') {
                if (nfaStack.empty()) return std::make_unique<NFA>();
                std::unique_ptr<NFA> subNFA = std::move(nfaStack.top());
                nfaStack.pop();

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
                if (oldAccept == NULL) return std::move(nfa);
                oldAccept->isAccepting = false;

                start->addTransition(EPSILON, subNFA->startState);
                start->addTransition(EPSILON, accept);
                oldAccept->addTransition(EPSILON, subNFA->startState);
                oldAccept->addTransition(EPSILON, accept);

                nfa->allStates.insert(nfa->allStates.end(),
                    subNFA->allStates.begin(), subNFA->allStates.end());
                subNFA->allStates.clear();
                nfaStack.push(std::move(nfa));
            }
            else if (c == '|') {
                if (nfaStack.size() < 2) return std::make_unique<NFA>();
                std::unique_ptr<NFA> nfaB = std::move(nfaStack.top()); nfaStack.pop();
                std::unique_ptr<NFA> nfaA = std::move(nfaStack.top()); nfaStack.pop();

                std::unique_ptr<NFA> nfa(new NFA());
                State* start = nfa->startState;
                State* accept = nfa->newState();
                accept->isAccepting = true;

                State* acceptA = NULL; State* acceptB = NULL;
                for (size_t j = 0; j < nfaA->allStates.size(); ++j)
                    if (nfaA->allStates[j]->isAccepting) { acceptA = nfaA->allStates[j]; break; }
                for (size_t j = 0; j < nfaB->allStates.size(); ++j)
                    if (nfaB->allStates[j]->isAccepting) { acceptB = nfaB->allStates[j]; break; }
                if (acceptA == NULL || acceptB == NULL) return std::move(nfa);

                acceptA->isAccepting = false;
                acceptB->isAccepting = false;
                start->addTransition(EPSILON, nfaA->startState);
                start->addTransition(EPSILON, nfaB->startState);
                acceptA->addTransition(EPSILON, accept);
                acceptB->addTransition(EPSILON, accept);

                nfa->allStates.insert(nfa->allStates.end(),
                    nfaA->allStates.begin(), nfaA->allStates.end());
                nfaA->allStates.clear();
                nfa->allStates.insert(nfa->allStates.end(),
                    nfaB->allStates.begin(), nfaB->allStates.end());
                nfaB->allStates.clear();
                nfaStack.push(std::move(nfa));
            }
            else if (c == '.') {
                if (nfaStack.size() < 2) return std::make_unique<NFA>();
                std::unique_ptr<NFA> nfaB = std::move(nfaStack.top()); nfaStack.pop();
                std::unique_ptr<NFA> nfaA = std::move(nfaStack.top()); nfaStack.pop();

                State* acceptA = NULL;
                for (size_t j = 0; j < nfaA->allStates.size(); ++j)
                    if (nfaA->allStates[j]->isAccepting) { acceptA = nfaA->allStates[j]; break; }
                if (acceptA == NULL) return std::move(nfaA);

                acceptA->isAccepting = false;
                acceptA->addTransition(EPSILON, nfaB->startState);
                nfaA->allStates.insert(nfaA->allStates.end(),
                    nfaB->allStates.begin(), nfaB->allStates.end());
                nfaB->allStates.clear();
                nfaStack.push(std::move(nfaA));
            }
        }

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
            State* s = stateStack.top();
            stateStack.pop();

            if (s->transitions.count(EPSILON)) {
                std::vector<State*>& nextStates = s->transitions[EPSILON];
                for (std::vector<State*>::iterator it = nextStates.begin();
                    it != nextStates.end(); ++it) {
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
                for (std::vector<State*>::iterator nextIt = nextStates.begin();
                    nextIt != nextStates.end(); ++nextIt) {
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

        // Build alphabet
        for (size_t i = 0; i < nfa->allStates.size(); ++i) {
            State* s = nfa->allStates[i];
            if (s == nullptr) continue;
            for (std::map<char, std::vector<State*>>::iterator it = s->transitions.begin();
                it != s->transitions.end(); ++it) {
                if (it->first != EPSILON) alphabet.insert(it->first);
            }
        }

        // Initial state
        std::set<State*> startNFAStates;
        startNFAStates.insert(nfa->startState);
        std::set<State*> startClosure = epsilonClosure(startNFAStates);
        if (startClosure.empty()) return dfa;

        dfa->startStateId = nextDfaId;
        dfaStateMap[startClosure] = nextDfaId++;
        dfa->dfaStateToNFAStates[dfa->startStateId] = startClosure;
        workQueue.push(startClosure);

        // Subset construction
        while (!workQueue.empty()) {
            std::set<State*> currentNFAStates = workQueue.front();
            workQueue.pop();
            int currentDFAId = dfaStateMap[currentNFAStates];

            // Check if accepting
            for (std::set<State*>::iterator it = currentNFAStates.begin();
                it != currentNFAStates.end(); ++it) {
                if ((*it)->isAccepting) {
                    dfa->acceptingStateIds.insert(currentDFAId);
                    break;
                }
            }

            // Build transitions
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

        // Try every starting position
        for (size_t start = 0; start < text.length(); ++start) {
            int currentState = dfa->startStateId;

            for (size_t end = start; end < text.length(); ++end) {
                char c = text[end];

                if (dfa->transitions.count(currentState) &&
                    dfa->transitions[currentState].count(c)) {
                    currentState = dfa->transitions[currentState].at(c);

                    if (dfa->acceptingStateIds.count(currentState)) {
                        matches.push_back(text.substr(start, end - start + 1));
                    }
                }
                else {
                    break;
                }
            }
        }

        return matches;
    }

    std::string generateNfaDot(NFA* nfa) {
        std::stringstream dot_ss;
        dot_ss << "digraph NFA {\n  rankdir=LR;\n  node [shape=circle];\n";

        if (nfa == nullptr || nfa->startState == nullptr) {
            dot_ss << "  error [label=\"Invalid NFA\"];\n}\n";
            return dot_ss.str();
        }

        dot_ss << "  start_node [shape=point];\n";
        dot_ss << "  start_node -> q" << nfa->startState->id << ";\n";

        for (size_t i = 0; i < nfa->allStates.size(); ++i) {
            State* s = nfa->allStates[i];
            if (s == nullptr) continue;
            if (s->isAccepting) dot_ss << "  q" << s->id << " [shape=doublecircle];\n";

            for (std::map<char, std::vector<State*>>::iterator it = s->transitions.begin();
                it != s->transitions.end(); ++it) {
                char key = it->first;
                std::vector<State*>& val = it->second;
                for (size_t j = 0; j < val.size(); ++j) {
                    State* next = val[j];
                    if (next == nullptr) continue;
                    std::string label = (key == EPSILON) ? "ε" : std::string(1, key);
                    dot_ss << "  q" << s->id << " -> q" << next->id
                        << " [label=\"" << label << "\"];\n";
                }
            }
        }
        dot_ss << "}\n";
        return dot_ss.str();
    }

    std::string generateDfaDot(DFA* dfa) {
        std::stringstream dot_ss;
        dot_ss << "digraph DFA {\n  rankdir=LR;\n  node [shape=circle];\n";

        if (dfa == nullptr) {
            dot_ss << "  error [label=\"Invalid DFA\"];\n}\n";
            return dot_ss.str();
        }

        dot_ss << "  start_node [shape=point];\n";
        dot_ss << "  start_node -> q" << dfa->startStateId << ";\n";

        for (std::set<int>::iterator it = dfa->acceptingStateIds.begin();
            it != dfa->acceptingStateIds.end(); ++it) {
            dot_ss << "  q" << *it << " [shape=doublecircle];\n";
        }

        for (std::map<int, std::map<char, int>>::iterator it = dfa->transitions.begin();
            it != dfa->transitions.end(); ++it) {
            int from = it->first;
            std::map<char, int>& table = it->second;
            for (std::map<char, int>::iterator it2 = table.begin();
                it2 != table.end(); ++it2) {
                dot_ss << "  q" << from << " -> q" << it2->second
                    << " [label=\"" << it2->first << "\"];\n";
            }
        }
        dot_ss << "}\n";
        return dot_ss.str();
    }

    std::string generateRightLinearGrammar(NFA* nfa) {
        std::stringstream grammar_ss;

        if (nfa == nullptr || nfa->startState == nullptr) {
            return "Error: Invalid NFA\n";
        }

        grammar_ss << "Right-Linear Grammar:\n";

        std::map<int, char> stateToNonTerminal;
        char nonTerminal = 'S';

        stateToNonTerminal[nfa->startState->id] = nonTerminal++;

        for (size_t i = 0; i < nfa->allStates.size(); ++i) {
            State* s = nfa->allStates[i];
            if (s != nfa->startState && stateToNonTerminal.find(s->id) == stateToNonTerminal.end()) {
                if (nonTerminal > 'Z') nonTerminal = 'A';
                stateToNonTerminal[s->id] = nonTerminal++;
            }
        }

        for (size_t i = 0; i < nfa->allStates.size(); ++i) {
            State* s = nfa->allStates[i];
            char fromNT = stateToNonTerminal[s->id];

            for (std::map<char, std::vector<State*>>::iterator it = s->transitions.begin();
                it != s->transitions.end(); ++it) {
                char symbol = it->first;
                if (symbol == EPSILON) continue;

                std::vector<State*>& nextStates = it->second;
                for (size_t j = 0; j < nextStates.size(); ++j) {
                    State* nextState = nextStates[j];
                    char toNT = stateToNonTerminal[nextState->id];
                    grammar_ss << fromNT << " -> " << symbol << toNT << "\n";
                }
            }

            if (s->isAccepting) {
                grammar_ss << fromNT << " -> ε\n";
            }
        }

        return grammar_ss.str();
    }

    std::string generateNfaGrammar(NFA* nfa) {
        return generateRightLinearGrammar(nfa);
    }

    std::string generateASCIIDiagram(NFA* nfa) {
        std::stringstream ascii_ss;

        if (nfa == nullptr || nfa->startState == nullptr) {
            return "Invalid NFA\n";
        }

        ascii_ss << "NFA Diagram:\n";
        for (size_t i = 0; i < nfa->allStates.size(); ++i) {
            State* s = nfa->allStates[i];
            if (s == nullptr) continue;

            std::string prefix = (s == nfa->startState) ? "→" : " ";
            std::string suffix = (s->isAccepting) ? "✓" : " ";
            ascii_ss << prefix << "(q" << s->id << ")" << suffix << "\n";
        }

        return ascii_ss.str();
    }

    std::string generateASCIIDiagram(DFA* dfa) {
        std::stringstream ascii_ss;

        if (dfa == nullptr) {
            return "Invalid DFA\n";
        }

        ascii_ss << "DFA Diagram:\n";
        ascii_ss << "Start: q" << dfa->startStateId << "\n";
        ascii_ss << "Accept: ";
        for (std::set<int>::iterator it = dfa->acceptingStateIds.begin();
            it != dfa->acceptingStateIds.end(); ++it) {
            ascii_ss << "q" << *it << " ";
        }
        ascii_ss << "\n";

        return ascii_ss.str();
    }

    // ========================================
    // LEVENSHTEIN NFA (FULL ASCII SUPPORT)
    // ========================================

    std::unique_ptr<NFA> buildLevenshteinNFA(const std::string& pattern, int maxErrors,
        std::stringstream& grammar_ss) {
        g_stateIdCounter = 0;
        std::unique_ptr<NFA> nfa(new NFA());

        grammar_ss << "Levenshtein NFA for: \"" << pattern << "\" (k=" << maxErrors << ")\n";

        std::map<std::pair<int, int>, State*> stateMap;
        int n = pattern.length();

        // Create states
        for (int pos = 0; pos <= n; ++pos) {
            for (int err = 0; err <= maxErrors; ++err) {
                State* state = (pos == 0 && err == 0) ? nfa->startState : nfa->newState();
                stateMap[std::make_pair(pos, err)] = state;

                if (pos == n) {
                    state->isAccepting = true;
                }
            }
        }

        // Create transitions - FULL PRINTABLE ASCII (32-126)
        for (int pos = 0; pos < n; ++pos) {
            for (int err = 0; err <= maxErrors; ++err) {
                State* currentState = stateMap[std::make_pair(pos, err)];
                char patternChar = pattern[pos];

                // Match
                State* matchState = stateMap[std::make_pair(pos + 1, err)];
                currentState->addTransition(patternChar, matchState);

                if (err < maxErrors) {
                    State* subState = stateMap[std::make_pair(pos + 1, err + 1)];
                    State* insState = stateMap[std::make_pair(pos, err + 1)];
                    State* delState = stateMap[std::make_pair(pos + 1, err + 1)];

                    // PROFESSOR'S FIX: Full printable ASCII (32-126)
                    for (char c = 32; c <= 126; ++c) {
                        if (c != patternChar) {
                            currentState->addTransition(c, subState);  // Substitution
                        }
                        currentState->addTransition(c, insState);  // Insertion
                    }

                    // Deletion
                    currentState->addTransition(EPSILON, delState);
                }
            }
        }

        grammar_ss << "Alphabet: Full printable ASCII (32-126)\n";
        return nfa;
    }

    std::vector<std::pair<std::string, int>> simulateLevenshteinNFA(NFA* nfa, const std::string& text,
        const std::string& pattern, int k) {
        std::set<std::pair<std::string, int>> uniqueMatches;

        for (size_t start = 0; start < text.length(); ++start) {
            std::queue<std::tuple<State*, size_t, int, std::string>> queue;
            std::set<std::tuple<int, size_t, int>> visited;

            std::set<State*> initialSet;
            initialSet.insert(nfa->startState);
            std::set<State*> initialClosure = epsilonClosure(initialSet);

            for (std::set<State*>::iterator it = initialClosure.begin();
                it != initialClosure.end(); ++it) {
                queue.push(std::make_tuple(*it, start, 0, ""));
            }

            while (!queue.empty()) {
                std::tuple<State*, size_t, int, std::string> current = queue.front();
                queue.pop();

                State* state = std::get<0>(current);
                size_t textPos = std::get<1>(current);
                int errors = std::get<2>(current);
                std::string matched = std::get<3>(current);

                std::tuple<int, size_t, int> key = std::make_tuple(state->id, textPos, errors);
                if (visited.count(key)) continue;
                visited.insert(key);

                if (state->isAccepting && matched.length() >= pattern.length() - k) {
                    uniqueMatches.insert(std::make_pair(matched, errors));
                }

                if (matched.length() > pattern.length() + k) continue;

                if (state->transitions.count(EPSILON)) {
                    std::vector<State*>& nextStates = state->transitions[EPSILON];
                    for (size_t i = 0; i < nextStates.size(); ++i) {
                        queue.push(std::make_tuple(nextStates[i], textPos, errors, matched));
                    }
                }

                if (textPos < text.length()) {
                    char c = text[textPos];
                    if (state->transitions.count(c)) {
                        std::vector<State*>& nextStates = state->transitions[c];
                        for (size_t i = 0; i < nextStates.size(); ++i) {
                            queue.push(std::make_tuple(nextStates[i], textPos + 1,
                                errors, matched + c));
                        }
                    }
                }
            }
        }

        std::vector<std::pair<std::string, int>> result(uniqueMatches.begin(), uniqueMatches.end());
        return result;
    }

    // ========================================
    // PDA STRUCTURES
    // ========================================

    struct PDATransition {
        int fromState;
        char inputSymbol;
        char stackTop;
        int toState;
        std::string stackPush;
    };

    struct PDASnapshot {
        int state;
        std::stack<char> stack;
        size_t inputPos;
        std::vector<std::string> path;

        std::string getStackString() const {
            std::stack<char> temp = stack;
            std::string result;
            while (!temp.empty()) {
                result = temp.top() + result;
                temp.pop();
            }
            return result.empty() ? "ε" : result;
        }
    };

    struct FormalPDA {
        std::vector<PDATransition> transitions;
        std::set<int> acceptStates;
        char stackStartSymbol;
        std::stringstream traceStream;
        bool accepted;

        FormalPDA() : stackStartSymbol('Z'), accepted(false) {}
    };

    // ========================================
    // DNA PDA (PROFESSOR'S FIX - ALL 4 BASES + LOOP)
    // ========================================

    std::unique_ptr<FormalPDA> buildDNAPDA() {
        std::unique_ptr<FormalPDA> pda(new FormalPDA());

        // States:
        // 0 = pushing first half (stem)
        // 1 = loop region (optional spacer)
        // 2 = popping second half (complementary stem)

        pda->acceptStates.insert(2);

        // PROFESSOR'S FIX: All 4 DNA bases can be pushed
        // State 0: Push ALL bases (G, A, T, C)
        pda->transitions.push_back({ 0, 'G', '\0', 0, "G" });
        pda->transitions.push_back({ 0, 'A', '\0', 0, "A" });
        pda->transitions.push_back({ 0, 'T', '\0', 0, "T" });
        pda->transitions.push_back({ 0, 'C', '\0', 0, "C" });

        // State 0 → State 1: Nondeterministic choice to enter loop
        pda->transitions.push_back({ 0, '\0', '\0', 1, "" });  // Epsilon to loop

        // State 1: Loop region (consume non-matching chars)
        pda->transitions.push_back({ 1, 'N', '\0', 1, "" });  // Loop spacer
        pda->transitions.push_back({ 1, '-', '\0', 1, "" });  // Hyphen spacer
        pda->transitions.push_back({ 1, ' ', '\0', 1, "" });  // Space spacer

        // State 1 → State 2: Nondeterministic choice to start matching
        pda->transitions.push_back({ 1, '\0', '\0', 2, "" });  // Epsilon to matching

        // State 0 → State 2: Direct transition (no loop case)
        pda->transitions.push_back({ 0, 'C', 'G', 2, "" });  // C matches G
        pda->transitions.push_back({ 0, 'T', 'A', 2, "" });  // T matches A
        pda->transitions.push_back({ 0, 'U', 'A', 2, "" });  // U matches A (RNA)
        pda->transitions.push_back({ 0, 'G', 'C', 2, "" });  // G matches C
        pda->transitions.push_back({ 0, 'A', 'T', 2, "" });  // A matches T
        pda->transitions.push_back({ 0, 'A', 'U', 2, "" });  // A matches U (RNA)

        // State 2: Continue matching complementary bases
        pda->transitions.push_back({ 2, 'C', 'G', 2, "" });
        pda->transitions.push_back({ 2, 'T', 'A', 2, "" });
        pda->transitions.push_back({ 2, 'U', 'A', 2, "" });
        pda->transitions.push_back({ 2, 'G', 'C', 2, "" });
        pda->transitions.push_back({ 2, 'A', 'T', 2, "" });
        pda->transitions.push_back({ 2, 'A', 'U', 2, "" });

        return pda;
    }

    std::unique_ptr<FormalPDA> buildBracketPDA() {
        std::unique_ptr<FormalPDA> pda(new FormalPDA());

        pda->acceptStates.insert(0);

        pda->transitions.push_back({ 0, '(', '\0', 0, "(" });
        pda->transitions.push_back({ 0, '[', '\0', 0, "[" });
        pda->transitions.push_back({ 0, '{', '\0', 0, "{" });

        pda->transitions.push_back({ 0, ')', '(', 0, "" });
        pda->transitions.push_back({ 0, ']', '[', 0, "" });
        pda->transitions.push_back({ 0, '}', '{', 0, "" });

        return pda;
    }

    std::unique_ptr<FormalPDA> buildXMLPDA() {
        std::unique_ptr<FormalPDA> pda(new FormalPDA());

        pda->acceptStates.insert(0);

        // Simplified: Push 'X' for opening tags, pop for closing
        pda->transitions.push_back({ 0, '<', '\0', 0, "X" });
        pda->transitions.push_back({ 0, '/', 'X', 0, "" });

        return pda;
    }

    // ========================================
    // NPDA SIMULATION (PROFESSOR'S FIX - BFS)
    // ========================================

    bool simulateFormalPDA(FormalPDA* pda, const std::string& input) {
        pda->traceStream.str("");
        pda->traceStream << std::left
            << std::setw(10) << "State"
            << std::setw(15) << "Input"
            << std::setw(20) << "Stack"
            << std::setw(25) << "Action" << "\n";
        pda->traceStream << std::string(70, '-') << "\n";

        // BFS Queue for nondeterministic simulation
        std::queue<PDASnapshot> queue;

        // Initial configuration
        PDASnapshot initial;
        initial.state = 0;
        initial.stack.push(pda->stackStartSymbol);
        initial.inputPos = 0;
        initial.path.push_back("START");
        queue.push(initial);

        std::set<std::string> visitedConfigs;  // Prevent infinite loops

        while (!queue.empty()) {
            PDASnapshot current = queue.front();
            queue.pop();

            // Create unique config signature
            std::stringstream configKey;
            configKey << current.state << ":" << current.inputPos << ":" << current.getStackString();
            std::string key = configKey.str();

            if (visitedConfigs.count(key)) continue;
            visitedConfigs.insert(key);

            // Log this step
            if (current.inputPos < input.length()) {
                pda->traceStream << std::setw(10) << current.state
                    << std::setw(15) << input[current.inputPos]
                    << std::setw(20) << current.getStackString()
                    << std::setw(25) << "Processing..." << "\n";
            }

            // Check acceptance: consumed all input + in accept state + stack has only start symbol
            if (current.inputPos >= input.length()) {
                bool stackOK = (current.stack.size() == 1 && current.stack.top() == pda->stackStartSymbol);
                bool stateOK = pda->acceptStates.count(current.state) > 0;

                if (stackOK && stateOK) {
                    pda->accepted = true;
                    pda->traceStream << "\n=== ACCEPTED ===\n";
                    pda->traceStream << "Final State: " << current.state << "\n";
                    pda->traceStream << "Final Stack: " << current.getStackString() << "\n";
                    return true;
                }
                continue;
            }

            char currentInput = input[current.inputPos];
            char stackTop = current.stack.empty() ? '\0' : current.stack.top();

            // Try ALL matching transitions (this is the nondeterminism)
            for (size_t i = 0; i < pda->transitions.size(); ++i) {
                PDATransition& trans = pda->transitions[i];

                // Check if transition applies
                if (trans.fromState != current.state) continue;

                bool inputMatches = (trans.inputSymbol == currentInput || trans.inputSymbol == '\0');
                bool stackMatches = (trans.stackTop == '\0' || trans.stackTop == stackTop);

                if (!inputMatches || !stackMatches) continue;

                // Create new configuration
                PDASnapshot next;
                next.state = trans.toState;
                next.stack = current.stack;
                next.inputPos = current.inputPos;
                next.path = current.path;

                // Stack operation
                if (trans.stackTop != '\0' && !next.stack.empty()) {
                    next.stack.pop();  // Pop if stackTop was specified
                }

                // Push new symbols (in reverse order)
                for (int j = trans.stackPush.length() - 1; j >= 0; --j) {
                    next.stack.push(trans.stackPush[j]);
                }

                // Advance input if not epsilon
                if (trans.inputSymbol != '\0') {
                    next.inputPos++;
                }

                // Log action
                std::stringstream action;
                if (trans.stackTop != '\0') action << "POP(" << trans.stackTop << ") ";
                if (!trans.stackPush.empty()) action << "PUSH(" << trans.stackPush << ")";
                if (trans.inputSymbol == '\0') action << " [ε-transition]";
                next.path.push_back(action.str());

                queue.push(next);
            }
        }

        // No accepting path found
        pda->accepted = false;
        pda->traceStream << "\n=== REJECTED ===\n";
        pda->traceStream << "No accepting configuration found.\n";
        return false;
    }

    std::string generateCFGForPDA(const std::string& mode) {
        std::stringstream ss;
        printHeader(ss, "Context-Free Grammar");

        if (mode == "BRACKET") {
            ss << "S -> (S) | [S] | {S} | SS | ε\n\n";
            ss << "This is context-free (NOT regular).\n";
            ss << "Proof: Pumping lemma for regular languages fails.\n";
        }
        else if (mode == "DNA" || mode == "RNA") {
            ss << "S -> GSC | AST | ASU | CGS | TAS | UAS\n";
            ss << "S -> SS | ε\n\n";
            ss << "Models DNA/RNA hairpin structures with complementary base pairing.\n";
            ss << "With loop: S -> W Loop W^R where W ∈ {G,A,T,C}*\n";
        }
        else if (mode == "XML") {
            ss << "S -> <tag>S</tag> | SS | ε\n\n";
            ss << "Simplified XML nesting grammar.\n";
        }

        return ss.str();
    }

    std::string GetTextFallback(const std::string& dot_string) {
        std::stringstream fallback_ss;
        fallback_ss << "ASCII Transition Table:\n";

        std::stringstream input_ss(dot_string);
        std::string line;

        while (std::getline(input_ss, line)) {
            size_t pos = line.find("->");
            if (pos != std::string::npos) {
                fallback_ss << line << "\n";
            }
        }

        return fallback_ss.str();
    }

    // ========================================
    // PUBLIC WRAPPER FUNCTIONS
    // ========================================

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

            printHeader(ss_summary, "Regex Search Engine");
            ss_summary << "Pattern:            " << regex << "\n";
            ss_summary << "Postfix:            " << postfix << "\n";
            ss_summary << "File:               " << filepath << "\n";
            ss_summary << "Strategy:           All-substring (overlapping)\n";
            ss_summary << "Escape Support:     ✓ (use \\ for literal . * | ( ) \\)\n";
            ss_summary << "Time Complexity:    O(N²·M)\n";
            ss_summary << "Execution Time:     " << duration.count() / 1000.0 << "s\n\n";

            ss_summary << "Note: Production engines use Aho-Corasick for O(N) multi-pattern search.\n";
            ss_summary << "Our O(N²) is acceptable for educational purposes and finds ALL matches.\n\n";

            ss_summary << "=== Statistics ===\n";
            ss_summary << "NFA States:         " << nfa->allStates.size() << "\n";
            ss_summary << "DFA States:         " << dfa->dfaStateToNFAStates.size() << "\n\n";

            ss_grammar << generateNfaGrammar(nfa.get());
            ss_grammar << "\n" << generateASCIIDiagram(dfa.get());

            printHeader(ss_results, "Match Report");
            ss_results << "Total: " << matches.size() << " matches\n\n";

            for (size_t i = 0; i < std::min(matches.size(), size_t(100)); ++i) {
                ss_results << std::setw(4) << (i + 1) << ": \"" << matches[i] << "\"\n";
            }

            if (matches.size() > 100) {
                ss_results << "\n... and " << (matches.size() - 100) << " more\n";
            }

            out_report.summary = ss_summary.str();
            out_report.grammar = ss_grammar.str();
            out_report.matches = ss_results.str();
        }
        catch (std::exception& e) {
            out_error_msg = "[Error] " + std::string(e.what());
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

            std::unique_ptr<NFA> levenshteinNFA = buildLevenshteinNFA(pattern, k, ss_grammar);
            std::vector<std::pair<std::string, int>> matches =
                simulateLevenshteinNFA(levenshteinNFA.get(), text, pattern, k);

            auto stop = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

            out_viz.nfaDot = generateNfaDot(levenshteinNFA.get());

            printHeader(ss_summary, "Approximate Matching (Levenshtein)");
            ss_summary << "Pattern:            \"" << pattern << "\"\n";
            ss_summary << "Max Errors (k):     " << k << "\n";
            ss_summary << "File:               " << filepath << "\n";
            ss_summary << "Alphabet:           Full printable ASCII (32-126)\n";
            ss_summary << "Execution Time:     " << duration.count() / 1000.0 << "s\n\n";

            ss_summary << "=== Statistics ===\n";
            int expectedStates = (pattern.length() + 1) * (k + 1);
            ss_summary << "NFA States:         " << levenshteinNFA->allStates.size()
                << " (Expected: " << expectedStates << ")\n\n";

            ss_summary << "=== Edit Operations ===\n";
            ss_summary << "Match:              Cost 0\n";
            ss_summary << "Substitution:       Cost 1\n";
            ss_summary << "Insertion:          Cost 1\n";
            ss_summary << "Deletion:           Cost 1 (ε-transition)\n\n";

            printHeader(ss_results, "Approximate Matches");
            ss_results << "Total: " << matches.size() << " matches\n\n";

            for (size_t i = 0; i < std::min(matches.size(), size_t(50)); ++i) {
                ss_results << std::setw(4) << (i + 1) << ": \""
                    << matches[i].first << "\" (distance: "
                    << matches[i].second << ")\n";
            }

            if (matches.size() > 50) {
                ss_results << "\n... and " << (matches.size() - 50) << " more\n";
            }

            out_report.summary = ss_summary.str();
            out_report.grammar = ss_grammar.str();
            out_report.matches = ss_results.str();
        }
        catch (std::exception& e) {
            out_error_msg = "[Error] " + std::string(e.what());
        }
    }

    void runBranch2B_logic(
        const std::string& input, bool isFile,
        SimulationReport& out_report, VisualizationData& out_viz, std::string& out_error_msg)
    {
        try {
            std::stringstream ss_summary, ss_results;
            std::string full_text = input;

            std::string mode = "BRACKET";
            if (isFile) {
                full_text = readFile(input);
                if (full_text.rfind("[Error]", 0) == 0) {
                    out_error_msg = full_text;
                    return;
                }

                if (input.find(".fasta") != std::string::npos ||
                    full_text.find('>') != std::string::npos) {
                    mode = "DNA";
                }
                else if (input.find(".xml") != std::string::npos ||
                    full_text.find('<') != std::string::npos) {
                    mode = "XML";
                }
            }

            out_report.grammar = generateCFGForPDA(mode);

            printHeader(ss_summary, "PDA Validation");
            ss_summary << "Mode:               " << mode << "\n";
            ss_summary << "Language Class:     Context-Free (Type-2)\n";
            ss_summary << "Recognizer:         Nondeterministic PDA\n";
            ss_summary << "Simulation:         BFS (explores all paths)\n\n";

            std::unique_ptr<FormalPDA> pda;
            if (mode == "DNA" || mode == "RNA") {
                pda = buildDNAPDA();
            }
            else if (mode == "XML") {
                pda = buildXMLPDA();
            }
            else {
                pda = buildBracketPDA();
            }

            bool isValid = simulateFormalPDA(pda.get(), full_text);

            printHeader(ss_results, "Validation Result");
            ss_results << "Input: " << (isFile ? input : full_text.substr(0, 50)) << "\n";
            ss_results << "Status: " << (isValid ? "✓ VALID" : "✗ INVALID") << "\n\n";

            out_viz.pdaTrace = pda->traceStream.str();

            out_report.summary = ss_summary.str();
            out_report.matches = ss_results.str();
        }
        catch (std::exception& e) {
            out_error_msg = "[Error] " + std::string(e.what());
        }
    }

    bool GenerateGraphvizImage(const std::string& dot_string, const std::string& image_path,
        std::string& out_error_message, std::string& out_fallback_text) {
        std::string dot_path = "temp_graph.dot";
        std::ofstream dot_file(dot_path);
        if (!dot_file.is_open()) {
            out_error_message = "Error: Could not write .dot file.";
            return false;
        }
        dot_file << dot_string;
        dot_file.close();

        std::string command = "dot -Tpng " + dot_path + " -o " + image_path;
        int result = system(command.c_str());

        if (result != 0) {
            out_error_message = "Error: Graphviz failed.";
            out_fallback_text = GetTextFallback(dot_string);
            return false;
        }
        return true;
    }

} // namespace GenoSearchEngine