#include "automaton_logic.h" 
#include "automaton.h"       
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
#include <cmath>
#include <tuple>

int g_stateIdCounter = 0;

namespace GenoSearchEngine {

    // ========================================
    //          FORWARD DECLARATIONS
    // ========================================
    struct PDAEngine;
    std::string generateNfaDot(NFA* nfa);
    std::string generateDfaDot(DFA* dfa);
    std::string generatePDADot(PDAEngine* pda);

    // ========================================
    //         BIO-VALIDATION HELPERS
    // ========================================
    bool isBioChar(char c) {
        char upper = std::toupper(static_cast<unsigned char>(c));
        return (upper == 'A' || upper == 'C' || upper == 'G' || upper == 'T' || upper == 'U' ||
            upper == 'N' || std::isspace(static_cast<unsigned char>(c)));
    }

    // Step 1: Input Validation
    bool validateBioContent(const std::string& text, std::string& errorOut) {
        for (size_t i = 0; i < text.length(); ++i) {
            char c = text[i];
            if (!isBioChar(c)) {
                errorOut = "Invalid Input: Non-biological character detected ('" + std::string(1, c) + "').\n"
                    "GenoSearch only accepts DNA/RNA sequences (A, C, G, T, U, N).";
                return false;
            }
        }
        return true;
    }

    // ========================================
    //         ESCAPE SEQUENCE TOKENS
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
    //          UTILITY FUNCTIONS
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

    void printTableRow(std::stringstream& ss, const std::string& label, const std::string& value) {
        const int TARGET_WIDTH = 18; // Adjust this number to make the gap wider/narrower

        // Calculate how many spaces we need
        int padding = TARGET_WIDTH - (int)label.length();
        if (padding < 0) padding = 0;

        //                                             Here is the change
        //                                                   vvvvv
        ss << label << std::string(padding, ' ') << ": " << value << "\r\n";
    }

    // PASTE THIS AFTER printTableRow function

    std::string centerText(std::string text, int width) {
        int visualLength = (int)text.length();

        // FIX: If text is Epsilon (2 bytes), treat it as length 1
        if (text == "ε") {
            visualLength = 1;
        }

        int padding = width - visualLength;
        if (padding <= 0) return text; // No padding needed

        int leftPad = padding / 2;
        int rightPad = padding - leftPad;

        return std::string(leftPad, ' ') + text + std::string(rightPad, ' ');
    }

    // ========================================
    //    SIMULATION 1: REGULAR EXPRESSION
    // ========================================

    int precedence(char op) {
        if (op == '*') return 3;
        if (op == '.') return 2;
        if (op == '|') return 1;
        return 0;
    }

	// Step 1 : Infix to Postfix Conversion with Escape Handling
    std::string infixToPostfix(const std::string& infix) {
        std::string processed;
        bool escapeNext = false;

        // 1. Handle Escapes
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

        // 2. Insert Explicit Concatenation (.)
        std::string formatted;
        for (size_t i = 0; i < processed.length(); ++i) {
            char c = processed[i];
            formatted += c;

            if (i + 1 < processed.length()) {
                char next = processed[i + 1];

                bool isLiteral = std::isalnum(c) || isEscapeToken(c);
                bool nextIsLiteral = std::isalnum(next) || isEscapeToken(next);

                bool cIsEnd = isLiteral || c == '*' || c == ')';
                bool nextIsStart = nextIsLiteral || next == '(';

                if (cIsEnd && nextIsStart) {
                    formatted += '.';
                }
            }
        }

        // 3. Convert to Postfix
        std::string postfix;
        std::stack<char> opStack;

        for (size_t i = 0; i < formatted.length(); ++i) {
            char c = formatted[i];
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

	// Step 2 : Thompson's Construction
    std::unique_ptr<NFA> buildThompson(const std::string& postfix) {
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
                if (nfaStack.empty()) continue;
                std::unique_ptr<NFA> subNFA = std::move(nfaStack.top());
                nfaStack.pop();

                std::unique_ptr<NFA> nfa(new NFA());
                State* start = nfa->startState;
                State* accept = nfa->newState();
                accept->isAccepting = true;

                for (size_t k = 0; k < subNFA->allStates.size(); ++k) {
                    State* s = subNFA->allStates[k];
                    if (s->isAccepting) {
                        s->isAccepting = false;
                        s->addTransition(EPSILON, subNFA->startState);
                        s->addTransition(EPSILON, accept);
                    }
                }

                start->addTransition(EPSILON, subNFA->startState);
                start->addTransition(EPSILON, accept);

                nfa->allStates.insert(nfa->allStates.end(), subNFA->allStates.begin(), subNFA->allStates.end());
                subNFA->allStates.clear();
                nfaStack.push(std::move(nfa));
            }
            else if (c == '|') {
                if (nfaStack.size() < 2) continue;
                std::unique_ptr<NFA> nfaB = std::move(nfaStack.top()); nfaStack.pop();
                std::unique_ptr<NFA> nfaA = std::move(nfaStack.top()); nfaStack.pop();

                std::unique_ptr<NFA> nfa(new NFA());
                State* start = nfa->startState;
                State* accept = nfa->newState();
                accept->isAccepting = true;

                for (size_t k = 0; k < nfaA->allStates.size(); ++k) {
                    State* s = nfaA->allStates[k];
                    if (s->isAccepting) { s->isAccepting = false; s->addTransition(EPSILON, accept); }
                }
                for (size_t k = 0; k < nfaB->allStates.size(); ++k) {
                    State* s = nfaB->allStates[k];
                    if (s->isAccepting) { s->isAccepting = false; s->addTransition(EPSILON, accept); }
                }

                start->addTransition(EPSILON, nfaA->startState);
                start->addTransition(EPSILON, nfaB->startState);

                nfa->allStates.insert(nfa->allStates.end(), nfaA->allStates.begin(), nfaA->allStates.end());
                nfa->allStates.insert(nfa->allStates.end(), nfaB->allStates.begin(), nfaB->allStates.end());

                nfaA->allStates.clear(); nfaB->allStates.clear();
                nfaStack.push(std::move(nfa));
            }
            else if (c == '.') {
                if (nfaStack.size() < 2) continue;
                std::unique_ptr<NFA> nfaB = std::move(nfaStack.top()); nfaStack.pop();
                std::unique_ptr<NFA> nfaA = std::move(nfaStack.top()); nfaStack.pop();

                for (size_t k = 0; k < nfaA->allStates.size(); ++k) {
                    State* s = nfaA->allStates[k];
                    if (s->isAccepting) {
                        s->isAccepting = false;
                        s->addTransition(EPSILON, nfaB->startState);
                    }
                }

                nfaA->allStates.insert(nfaA->allStates.end(), nfaB->allStates.begin(), nfaB->allStates.end());
                nfaB->allStates.clear();
                nfaStack.push(std::move(nfaA));
            }
        }

        if (nfaStack.empty()) return std::unique_ptr<NFA>(new NFA());
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
                for (size_t i = 0; i < nextStates.size(); ++i) {
                    State* next = nextStates[i];
                    if (closure.find(next) == closure.end()) {
                        closure.insert(next);
                        stateStack.push(next);
                    }
                }
            }
        }
        return closure;
    }

	//Step 3 : Subset Construction (NFA to DFA)
    std::unique_ptr<DFA> buildDFA(NFA* nfa) {
        std::unique_ptr<DFA> dfa(new DFA());
        if (!nfa || !nfa->startState) return dfa;

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

        std::set<State*> startSet;
        startSet.insert(nfa->startState);
        std::set<State*> startClosure = epsilonClosure(startSet);

        dfa->startStateId = nextDfaId;
        dfaStateMap[startClosure] = nextDfaId++;
        dfa->dfaStateToNFAStates[dfa->startStateId] = startClosure;
        workQueue.push(startClosure);

        while (!workQueue.empty()) {
            std::set<State*> current = workQueue.front(); workQueue.pop();
            int currentId = dfaStateMap[current];

            for (std::set<State*>::iterator it = current.begin(); it != current.end(); ++it) {
                if ((*it)->isAccepting) {
                    dfa->acceptingStateIds.insert(currentId);
                    break;
                }
            }

            for (std::set<char>::iterator it = alphabet.begin(); it != alphabet.end(); ++it) {
                char c = *it;
                std::set<State*> moved;
                for (std::set<State*>::iterator sit = current.begin(); sit != current.end(); ++sit) {
                    State* s = *sit;
                    if (s->transitions.count(c)) {
                        std::vector<State*>& vec = s->transitions[c];
                        for (size_t v = 0; v < vec.size(); ++v) moved.insert(vec[v]);
                    }
                }

                if (moved.empty()) continue;
                std::set<State*> nextClosure = epsilonClosure(moved);

                int nextId;
                if (dfaStateMap.find(nextClosure) == dfaStateMap.end()) {
                    nextId = nextDfaId++;
                    dfaStateMap[nextClosure] = nextId;
                    dfa->dfaStateToNFAStates[nextId] = nextClosure;
                    workQueue.push(nextClosure);
                }
                else {
                    nextId = dfaStateMap[nextClosure];
                }
                dfa->transitions[currentId][c] = nextId;
            }
        }
        return dfa;
    }

	//Step 4 : Simulation 
    std::vector<std::string> simulateDFA(DFA* dfa, const std::string& text) {
        std::vector<std::string> matches;

        // Brute force substring search
        for (size_t i = 0; i < text.length(); ++i) {
            int current = dfa->startStateId;
            for (size_t j = i; j < text.length(); ++j) {
                char c = text[j];
                if (dfa->transitions[current].count(c)) {
                    current = dfa->transitions[current][c];
                    if (dfa->acceptingStateIds.count(current)) {
                        matches.push_back(text.substr(i, j - i + 1));
                    }
                }
                else {
                    break;
                }
            }
        }
        return matches;
    }

    // ========================================
    //     SIMULATION 2: APPROXIMATE MATCH
    // ========================================

    const char LEV_EPSILON = '\0';
    const char LEV_SUB = '*';
    const char LEV_INS = '+';

	//Step 1: Grid NFA Construction
    std::unique_ptr<NFA> buildLevenshteinNFA(const std::string& pattern, int maxErrors) {
        g_stateIdCounter = 0;
        std::unique_ptr<NFA> nfa(new NFA());

        std::map<std::pair<int, int>, State*> stateMap;
        int n = (int)pattern.length();

        for (int i = 0; i <= n; ++i) {
            for (int e = 0; e <= maxErrors; ++e) {
                State* s = (i == 0 && e == 0) ? nfa->startState : nfa->newState();
                stateMap[std::make_pair(i, e)] = s;
                if (i == n) s->isAccepting = true;
            }
        }

        for (int i = 0; i < n; ++i) {
            for (int e = 0; e <= maxErrors; ++e) {
                State* current = stateMap[std::make_pair(i, e)];
                char pChar = pattern[i];

                current->addTransition(pChar, stateMap[std::make_pair(i + 1, e)]);

                if (e < maxErrors) {
                    current->addTransition(LEV_SUB, stateMap[std::make_pair(i + 1, e + 1)]);
                    current->addTransition(LEV_INS, stateMap[std::make_pair(i, e + 1)]);
                    current->addTransition(LEV_EPSILON, stateMap[std::make_pair(i + 1, e + 1)]);
                }
            }
        }
        return nfa;
    }

    std::vector<std::pair<std::string, int>> simulateLevenshteinNFA(NFA* nfa, const std::string& text, const std::string& pattern, int k) {
        const char LOCAL_EPSILON = '\0';
        const char LOCAL_SUB_WILDCARD = '*';
        const char LOCAL_INS_WILDCARD = '+';

        auto cleanString = [](const std::string& s) -> std::string {
            std::string result;
            for (char c : s) {
                if (!std::isspace(static_cast<unsigned char>(c)) && std::isprint(static_cast<unsigned char>(c))) {
                    result += c;
                }
            }
            return result;
            };

        std::map<std::string, int> bestMatches;

        typedef std::tuple<State*, size_t, int, std::string, int> SearchState;

        auto start_time = std::chrono::steady_clock::now();

		//Step 2: Pipeline Initialization
        for (size_t startPos = 0; startPos < text.length(); ++startPos) {
            auto now = std::chrono::steady_clock::now();
            if (std::chrono::duration_cast<std::chrono::seconds>(now - start_time).count() > 5) break;

			//Step 3: BFS Simulation
            std::queue<SearchState> localQ;
            std::set<std::tuple<int, size_t, int>> visited;

            // Start search at this text position
            localQ.push(std::make_tuple(nfa->startState, startPos, 0, std::string(""), 0));

            while (!localQ.empty()) {
                SearchState currentTuple = localQ.front();
                localQ.pop();

                State* currState = std::get<0>(currentTuple);
                size_t txtIdx = std::get<1>(currentTuple);
                int err = std::get<2>(currentTuple);
                std::string accStr = std::get<3>(currentTuple);
                int patIdx = std::get<4>(currentTuple);

                // Step 4: Pruning
                std::tuple<int, size_t, int> visitKey = std::make_tuple(currState->id, txtIdx, err);
                if (visited.count(visitKey)) continue;
                visited.insert(visitKey);

                // CAPTURE RESULT
                if (currState->isAccepting && patIdx == (int)pattern.length()) {
                    // Clean the string (remove \r, \n, etc) before checking duplicates
                    std::string clean = cleanString(accStr);
                    if (!clean.empty()) {
						//Step 5.A : Deduplication 
                        if (bestMatches.find(clean) == bestMatches.end() || err < bestMatches[clean]) {
                            bestMatches[clean] = err;
                        }
                    }
                }

                // Safety clamp
                if (accStr.length() > pattern.length() + k + 1) continue;

                // --- Transitions ---

                // 1. Epsilon (Deletion in pattern)
                if (currState->transitions.count(LOCAL_EPSILON)) {
                    std::vector<State*>& nextStates = currState->transitions[LOCAL_EPSILON];
                    for (size_t v = 0; v < nextStates.size(); ++v) {
                        if (err + 1 <= k) {
                            localQ.push(std::make_tuple(nextStates[v], txtIdx, err + 1, accStr, patIdx + 1));
                        }
                    }
                }

                if (txtIdx < text.length()) {
                    char c = text[txtIdx];

                    // 2. Exact Match
                    if (currState->transitions.count(c)) {
                        std::vector<State*>& nextStates = currState->transitions[c];
                        for (size_t v = 0; v < nextStates.size(); ++v) {
                            localQ.push(std::make_tuple(nextStates[v], txtIdx + 1, err, accStr + c, patIdx + 1));
                        }
                    }

                    // 3. Substitution
                    if (currState->transitions.count(LOCAL_SUB_WILDCARD)) {
                        std::vector<State*>& nextStates = currState->transitions[LOCAL_SUB_WILDCARD];
                        for (size_t v = 0; v < nextStates.size(); ++v) {
                            if (err + 1 <= k) {
                                localQ.push(std::make_tuple(nextStates[v], txtIdx + 1, err + 1, accStr + c, patIdx + 1));
                            }
                        }
                    }

                    // 4. Insertion
                    if (currState->transitions.count(LOCAL_INS_WILDCARD)) {
                        std::vector<State*>& nextStates = currState->transitions[LOCAL_INS_WILDCARD];
                        for (size_t v = 0; v < nextStates.size(); ++v) {
                            if (err + 1 <= k) {
                                localQ.push(std::make_tuple(nextStates[v], txtIdx + 1, err + 1, accStr + c, patIdx));
                            }
                        }
                    }
                }
            }
        }

        std::vector<std::pair<std::string, int>> rawResults;
        for (std::map<std::string, int>::iterator it = bestMatches.begin(); it != bestMatches.end(); ++it) {
            rawResults.push_back(*it);
        }

        struct {
            bool operator()(const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) const {
                if (a.second != b.second) return a.second < b.second; 
                return a.first.length() > b.first.length();           
            }
        } sorter;
        std::sort(rawResults.begin(), rawResults.end(), sorter);

        std::vector<std::pair<std::string, int>> finalResults;

        //Step 5.B: Substring Removal
        for (size_t i = 0; i < rawResults.size(); ++i) {
            bool isRedundant = false;
            for (size_t j = 0; j < finalResults.size(); ++j) {
                if (finalResults[j].first.find(rawResults[i].first) != std::string::npos) {
                    isRedundant = true;
                    break;
                }
            }
            if (!isRedundant) {
                finalResults.push_back(rawResults[i]);
            }
            if (finalResults.size() >= 100) break;
        }

        return finalResults;
    }

    // ===========================================
    //     SIMULATION 3: STRUCTURAL VALIDATION
    // ===========================================

    struct PDATransition {
        int from;
        char input;
        char pop;
        int to;
        std::string push;
    };

    struct TraceStep {
        int stateId;
        std::string stackContent;
        char inputRaw;
        char popRaw;
        std::string pushRaw;
        bool isInitial;
    };

    struct PDAEngine {
        std::vector<PDATransition> transitions;
        std::set<int> acceptStates;
        char startSymbol;
        std::stringstream trace;
        int maxStackDepth;
        bool accepted;
        int traceLines;

        std::vector<TraceStep> executionPath;

        PDAEngine() : maxStackDepth(0), accepted(false), traceLines(0), startSymbol('Z') {}

        void addTrace(int state, char input, const std::string& stackStr, const std::string& action) {
            if (traceLines < 10) {
                trace << std::left << std::setw(10) << state
                    << std::setw(10) << (input == '\0' ? "epsilon" : std::string(1, input))
                    << std::setw(15) << (stackStr.empty() ? "epsilon" : stackStr)
                    << action;
                traceLines++;
            }
            else if (traceLines == 10) {
                trace << "... (trace truncated) ...\n";
                traceLines++;
            }
        }
    };

	// Step 2: PDA Construction for Nucleotide Pairing
    std::unique_ptr<PDAEngine> buildNucleotidePDA() {
        std::unique_ptr<PDAEngine> pda(new PDAEngine());
        pda->startSymbol = 'Z';
        pda->acceptStates.insert(2);

        PDATransition t;

        // PHASE 1: PUSH RULES (State 0)
        t = { 0, 'G', '\0', 0, "G" }; pda->transitions.push_back(t);
        t = { 0, 'C', '\0', 0, "C" }; pda->transitions.push_back(t);
        t = { 0, 'A', '\0', 0, "A" }; pda->transitions.push_back(t);
        t = { 0, 'T', '\0', 0, "T" }; pda->transitions.push_back(t);
        t = { 0, 'U', '\0', 0, "U" }; pda->transitions.push_back(t); // Added RNA

        // MIDPOINT: SWITCH (State 0 -> State 1)
        t = { 0, '\0', '\0', 1, "" }; pda->transitions.push_back(t);

        // PHASE 2: POP RULES (State 1)
        t = { 1, 'C', 'G', 1, "" }; pda->transitions.push_back(t); // G-C
        t = { 1, 'G', 'C', 1, "" }; pda->transitions.push_back(t); // C-G

        // DNA Pairing
        t = { 1, 'T', 'A', 1, "" }; pda->transitions.push_back(t); // A-T
        t = { 1, 'A', 'T', 1, "" }; pda->transitions.push_back(t); // T-A

        // RNA Pairing
        t = { 1, 'U', 'A', 1, "" }; pda->transitions.push_back(t); // A-U
        t = { 1, 'A', 'U', 1, "" }; pda->transitions.push_back(t); // U-A

        // ACCEPT: Empty Stack Check (State 1 -> State 2)
        t = { 1, '\0', 'Z', 2, "Z" }; pda->transitions.push_back(t);

        return pda;
    }


    bool simulatePDA(PDAEngine* pda, const std::string& input) {
        struct Config {
            int state;
            size_t inputIdx;
            std::vector<char> stack;
            std::vector<std::string> history;     // Store valid path history
            std::vector<TraceStep> structHistory; // New Data History
            int pathMaxDepth;                     // Track max depth for THIS path only
        };

        std::queue<Config> q;
        std::vector<char> startStack;
        startStack.push_back(pda->startSymbol);

        Config startConfig;
        startConfig.state = 0;
        startConfig.inputIdx = 0;
        startConfig.stack = startStack;
        startConfig.pathMaxDepth = 1;    

        // Record Initial State
        TraceStep initialStep;
        initialStep.stateId = 0;
        initialStep.stackContent = std::string(1, pda->startSymbol);
        initialStep.isInitial = true;       
        startConfig.structHistory.push_back(initialStep);

        q.push(startConfig);

        // Reset global metrics
        pda->maxStackDepth = 0;
        pda->accepted = false; // Reset accepted status
        pda->executionPath.clear();
        int iterations = 0;

		//Step 3: Simulation with History Tracking
        while (!q.empty()) {
            if (iterations++ > 30000) break; // Safety break

            Config curr = q.front(); q.pop();

            // Stack String for Trace
            std::string stackStr;
            for (std::vector<char>::reverse_iterator it = curr.stack.rbegin(); it != curr.stack.rend(); ++it) stackStr += *it;

            // Step 4: Acceptance Check
            if (curr.inputIdx == input.length() && pda->acceptStates.count(curr.state)) {
                // Stack must be effectively empty (just start symbol)
                if (curr.stack.size() == 1 && curr.stack.back() == pda->startSymbol) {

                    // FOUND IT! 
                    // 1. Update Global Max Depth with THIS path's max
                    pda->maxStackDepth = curr.pathMaxDepth;
                    pda->accepted = true;

                    // Save the structured path for the Diagram
                    pda->executionPath = curr.structHistory;

                    // 2. Overwrite the trace with ONLY this winning history
                    pda->trace.str("");
                    // CENTERED HEADERS
                    pda->trace << centerText("State", 10)
                        << centerText("Input", 10)
                        << centerText("Stack", 15)
                        << "Action\r\n";
                    pda->trace << "---------------------------------------------\r\n";

                    // Print the history of the winner
                    size_t limit = std::min((size_t)12, curr.history.size());
                    for (size_t i = 0; i < limit; ++i) {
                        pda->trace << curr.history[i] << "\r\n";
                    }
                    if (curr.history.size() > 12) pda->trace << "... (trace truncated) ...\r\n";

                    pda->trace << "\r\n>>> ACCEPTED <<<\r\n";
                    return true;
                }
            }

            char inputChar = (curr.inputIdx < input.length()) ? input[curr.inputIdx] : '\0';
            char stackTop = curr.stack.empty() ? '\0' : curr.stack.back();

            for (size_t i = 0; i < pda->transitions.size(); ++i) {
                const PDATransition& t = pda->transitions[i];
                if (t.from != curr.state) continue;

                // Input Match?
                bool matchInput = (t.input == '\0') || (t.input == inputChar);
                if (!matchInput) continue;

                // Stack Match?
                bool matchStack = (t.pop == '\0') || (t.pop == stackTop);
                if (!matchStack) continue;

                // Execute Transition
                Config next = curr;
                next.state = t.to;
                if (t.input != '\0') next.inputIdx++;
                if (t.pop != '\0') next.stack.pop_back();
                for (int j = (int)t.push.length() - 1; j >= 0; --j) {
                    next.stack.push_back(t.push[j]);
                }
                if ((int)next.stack.size() > next.pathMaxDepth) {
                    next.pathMaxDepth = (int)next.stack.size();
                }

                // RECORD HISTORY for this specific path
                std::stringstream actionSS;
                std::string actionName;
                if (t.input == '\0' && t.pop == '\0' && t.push.empty()) actionName = "Switch";
                else {
                    if (t.input == '\0') actionName += "ε ";
                    if (t.pop != '\0') actionName += "Pop " + std::string(1, t.pop) + " ";
                    if (!t.push.empty()) actionName += "Push " + t.push;
                }

                // Prepare strings for centering
                std::string s_state = std::to_string(curr.state);
                std::string s_input = (t.input == '\0' ? "ε" : std::string(1, inputChar));
                std::string s_stack = (stackStr.empty() ? "ε" : stackStr);

                // USE CENTERTEXT TO FIX ZIGZAG
                actionSS << centerText(s_state, 10)
                    << centerText(s_input, 10)
                    << centerText(s_stack, 15)
                    << actionName;

                next.history.push_back(actionSS.str());
                
				// Record structured step
                TraceStep step;
                step.stateId = next.state;
                step.isInitial = false;

                // Save the stack state of the NEW node
                std::string nextStackStr;
                for (std::vector<char>::reverse_iterator it = next.stack.rbegin(); it != next.stack.rend(); ++it) nextStackStr += *it;
                step.stackContent = nextStackStr;

                // Save the TRANSITION that got us here
                step.inputRaw = t.input;
                step.popRaw = t.pop;
                step.pushRaw = t.push;

                next.structHistory.push_back(step);
                q.push(next);
            }
        }
        return false;
    }

    // ========================================
    //      OUTPUT GENERATORS (CLEAN)
    // ========================================

    void generateRegexSummary(const std::string& regex, const std::string& file, double time, const std::vector<std::string>& matches, SimulationReport& report) {
        std::stringstream ss;
        printTableRow(ss, "Search mode", "Exact (Regex)");
        printTableRow(ss, "Pattern", regex);
        printTableRow(ss, "Input file", file);
        printTableRow(ss, "Execution time", std::to_string(time) + " s");
        printTableRow(ss, "Total matches", std::to_string(matches.size()));

        std::string topMatches;
        for (size_t i = 0; i < std::min(matches.size(), (size_t)10); ++i) topMatches += matches[i] + " ";
        if (matches.size() > 10) topMatches += "...";
        printTableRow(ss, "Top matches", topMatches);

        report.summary = ss.str();
    }

    void generateRegexConfig(int nfaStates, int dfaStates, int alphabet, const std::string& postfix, SimulationReport& report) {
        std::stringstream ss;
        printTableRow(ss, "NFA state count", std::to_string(nfaStates));
        printTableRow(ss, "DFA state count", std::to_string(dfaStates));
        printTableRow(ss, "Alphabet size", std::to_string(alphabet));
        printTableRow(ss, "Postfix form", postfix);
        report.grammar = ss.str();
    }

    void generateRegexDetails(const std::vector<std::string>& matches, SimulationReport& report) {
        std::stringstream ss;
        if (matches.empty()) {
            ss << "(No matches found)\n";
        }
        else {
            size_t minL = matches[0].length(), maxL = matches[0].length();
            ss << "Sample Matches (First 10):\n";
            for (size_t i = 0; i < std::min(matches.size(), (size_t)10); ++i) {
                if (matches[i].length() < minL) minL = matches[i].length();
                if (matches[i].length() > maxL) maxL = matches[i].length();
                ss << std::setw(3) << (i + 1) << ": " << matches[i] << "\n";
            }
            ss << "\n";
            printTableRow(ss, "Shortest match", std::to_string(minL));
            printTableRow(ss, "Longest match", std::to_string(maxL));
        }
        report.matches = ss.str();
    }

    void generateFuzzySummary(const std::string& pat, int k, const std::string& file, double time, const std::vector<std::pair<std::string, int> >& matches, SimulationReport& report) {
        std::stringstream ss;
        printTableRow(ss, "Search mode", "Approximate (Levenshtein)");
        printTableRow(ss, "Pattern", pat);
        printTableRow(ss, "k-value", std::to_string(k));
        printTableRow(ss, "Input file", file);
        printTableRow(ss, "Execution time", std::to_string(time) + " s");
        printTableRow(ss, "Total matches", std::to_string(matches.size()));
        report.summary = ss.str();
    }

    void generateFuzzyConfig(const std::string& pat, int k, int nfaStates, SimulationReport& report) {
        std::stringstream ss;
        printTableRow(ss, "Pattern length", std::to_string(pat.length()));
        printTableRow(ss, "k value", std::to_string(k));
        printTableRow(ss, "NFA state count", std::to_string(nfaStates));
        printTableRow(ss, "Grid dimension", std::to_string(pat.length() + 1) + " x " + std::to_string(k + 1));
        printTableRow(ss, "Edit operations", "Insert, Delete, Substitute");
        report.grammar = ss.str();
    }

    void generateFuzzyDetails(const std::vector<std::pair<std::string, int> >& matches, SimulationReport& report) {
        std::stringstream ss;
        if (matches.empty()) {
            ss << "(No matches found)\n";
        }
        else {
            int minErr = 9999, maxErr = 0;
            ss << "Sample Matches (First 10):\n";
            for (size_t i = 0; i < std::min(matches.size(), (size_t)10); ++i) {
                int e = matches[i].second;
                if (e < minErr) minErr = e;
                if (e > maxErr) maxErr = e;
                ss << std::setw(3) << (i + 1) << ": " << matches[i].first << " (err: " << e << ")\n";
            }
            ss << "\n";
            printTableRow(ss, "Best match error", std::to_string(minErr));
            printTableRow(ss, "Max error observed", std::to_string(maxErr));
        }
        report.matches = ss.str();
    }

    void generatePDASummary(const std::string& mode, size_t len, double time, bool valid, int depth, SimulationReport& report) {
        std::stringstream ss;
        printTableRow(ss, "Structure type", mode);
        printTableRow(ss, "Input length", std::to_string(len));
        printTableRow(ss, "Execution time", std::to_string(time) + " s");
        printTableRow(ss, "Result", valid ? "ACCEPTED" : "REJECTED");
        printTableRow(ss, "Max stack depth", std::to_string(depth));
        report.summary = ss.str();
    }

    void generatePDAConfig(const std::string& mode, int transitions, int accepts, char start, SimulationReport& report) {
        std::stringstream ss;
        printTableRow(ss, "Total transitions", std::to_string(transitions));
        printTableRow(ss, "Accept state count", std::to_string(accepts));
        printTableRow(ss, "Start stack symbol", std::string(1, start));
        report.grammar = ss.str();
    }

    // ========================================
    //      MAIN WRAPPERS
    // ========================================

    void runBranch1_logic(const std::string& regex, const std::string& filepath, SimulationReport& out_report, VisualizationData& out_viz, std::string& out_error_msg) {
        try {
            std::string text = readFile(filepath);
            if (text.rfind("[Error]", 0) == 0) { out_error_msg = text; return; }
            if (!validateBioContent(text, out_error_msg)) return;

            auto start = std::chrono::high_resolution_clock::now();
            std::string postfix = infixToPostfix(regex);
            std::unique_ptr<NFA> nfa = buildThompson(postfix);
            std::unique_ptr<DFA> dfa = buildDFA(nfa.get());
            std::vector<std::string> matches = simulateDFA(dfa.get(), text);
            auto end = std::chrono::high_resolution_clock::now();

            double time = std::chrono::duration<double>(end - start).count();

            out_viz.nfaDot = generateNfaDot(nfa.get());
            out_viz.dfaDot = generateDfaDot(dfa.get());

            generateRegexSummary(regex, filepath, time, matches, out_report);
            generateRegexConfig((int)nfa->allStates.size(), (int)dfa->dfaStateToNFAStates.size(), 4, postfix, out_report);
            generateRegexDetails(matches, out_report);

        }
        catch (std::exception& e) { out_error_msg = e.what(); }
    }

    void runBranch2A_logic(const std::string& pattern, int k, const std::string& filepath, SimulationReport& out_report, VisualizationData& out_viz, std::string& out_error_msg) {
        try {
            std::string text = readFile(filepath);
            if (text.rfind("[Error]", 0) == 0) { out_error_msg = text; return; }
            if (!validateBioContent(text, out_error_msg)) return;
            // Validate Pattern too
            std::string patErr;
            if (!validateBioContent(pattern, patErr)) { out_error_msg = "Pattern Error: " + patErr; return; }

            auto start = std::chrono::high_resolution_clock::now();
            std::unique_ptr<NFA> nfa = buildLevenshteinNFA(pattern, k);
            std::vector<std::pair<std::string, int> > matches = simulateLevenshteinNFA(nfa.get(), text, pattern, k);
            auto end = std::chrono::high_resolution_clock::now();

            double time = std::chrono::duration<double>(end - start).count();

            out_viz.nfaDot = generateNfaDot(nfa.get());

            generateFuzzySummary(pattern, k, filepath, time, matches, out_report);
            generateFuzzyConfig(pattern, k, (int)nfa->allStates.size(), out_report);
            generateFuzzyDetails(matches, out_report);

        }
        catch (std::exception& e) { out_error_msg = e.what(); }
    }

    void runBranch2B_logic(const std::string& input, bool isFile, SimulationReport& out_report, VisualizationData& out_viz, std::string& out_error_msg) {
        try {
            std::string text = input;
            if (isFile) {
                text = readFile(input);
                if (text.rfind("[Error]", 0) == 0) { out_error_msg = text; return; }
            }

            // 1. STRICT BIO VALIDATION (No XML, No Brackets)
            if (!validateBioContent(text, out_error_msg)) return;

            std::string mode = "Nucleotide Palindrome";

            auto start = std::chrono::steady_clock::now();

            // 2. Use the new Unified Builder
            std::unique_ptr<PDAEngine> pda = buildNucleotidePDA();

            // 3. Strip whitespace for cleaner trace processing
            std::string cleanText;
            for (size_t i = 0; i < text.length(); ++i) {
                if (!std::isspace(static_cast<unsigned char>(text[i]))) cleanText += text[i];
            }

            bool valid = simulatePDA(pda.get(), cleanText);
            auto end = std::chrono::steady_clock::now();
            double time = std::chrono::duration<double>(end - start).count();

            generatePDASummary(mode, cleanText.length(), time, valid, pda->maxStackDepth, out_report);
            generatePDAConfig(mode, (int)pda->transitions.size(), (int)pda->acceptStates.size(), pda->startSymbol, out_report);

            out_report.matches = pda->trace.str();
            if (out_report.matches.empty()) out_report.matches = "Trace unavailable (Sequence Rejected)";

            out_viz.pdaTrace = out_report.matches;
            out_viz.pdaDot = generatePDADot(pda.get()); 

        }
        catch (std::exception& e) { out_error_msg = e.what(); }
    }

    // ========================================
    //      DOT GENERATION
    // ========================================

    std::string generateNfaDot(NFA* nfa) {
        std::stringstream dot_ss;
        dot_ss << "digraph NFA {\n  rankdir=LR;\n  node [shape=circle];\n";
        if (!nfa || !nfa->startState) return "digraph G {}";

        dot_ss << "  start [shape=point];\n  start -> " << nfa->startState->id << ";\n";
        for (size_t i = 0; i < nfa->allStates.size(); ++i) {
            State* s = nfa->allStates[i];
            if (s->isAccepting) dot_ss << "  " << s->id << " [shape=doublecircle];\n";
            else dot_ss << "  " << s->id << " [shape=circle];\n";

            for (std::map<char, std::vector<State*> >::iterator it = s->transitions.begin(); it != s->transitions.end(); ++it) {
                char k = it->first;
                std::vector<State*>& v = it->second;
                for (size_t j = 0; j < v.size(); ++j) {
                    State* next = v[j];
                    std::string label;
                    if (k == '\0') label = "&epsilon;";
                    else if (k == '*') label = "sub(*)";
                    else if (k == '+') label = "ins(+)";
                    else label = std::string(1, k);
                    dot_ss << "  " << s->id << " -> " << next->id << " [label=\"" << label << "\"];\n";
                }
            }
        }
        dot_ss << "}\n";
        return dot_ss.str();
    }

    std::string generateDfaDot(DFA* dfa) {
        std::stringstream dot_ss;
        dot_ss << "digraph DFA {\n  rankdir=LR;\n  node [shape=circle];\n";
        if (!dfa) return "digraph G {}";

        dot_ss << "  start [shape=point];\n  start -> " << dfa->startStateId << ";\n";
        for (std::set<int>::iterator it = dfa->acceptingStateIds.begin(); it != dfa->acceptingStateIds.end(); ++it) {
            dot_ss << "  " << *it << " [shape=doublecircle];\n";
        }

        for (std::map<int, std::map<char, int> >::iterator it = dfa->transitions.begin(); it != dfa->transitions.end(); ++it) {
            int from = it->first;
            std::map<char, int>& table = it->second;
            for (std::map<char, int>::iterator t_it = table.begin(); t_it != table.end(); ++t_it) {
                dot_ss << "  " << from << " -> " << t_it->second << " [label=\"" << t_it->first << "\"];\n";
            }
        }
        dot_ss << "}\n";
        return dot_ss.str();
    }

    std::string GetTextFallback(const std::string& dot_string) {
        return "Graphviz not available. Text representation: \n" + dot_string;
    }

    std::string generatePDADot(PDAEngine* pda) {
        if (!pda) return "digraph G {}";

        std::stringstream dot_ss;

        // MODE A: If we have a linear trace (Accepted), draw the Timeline
        if (pda->accepted && !pda->executionPath.empty()) {
            dot_ss << "digraph PDA_Trace {\n";
            dot_ss << "  rankdir=LR;\n";
            dot_ss << "  node [shape=circle];\n"; // Standard Circles

            for (size_t i = 0; i < pda->executionPath.size(); ++i) {
                TraceStep& step = pda->executionPath[i];

                // Draw State Node (Just the number)
                // Use doublecircle for the very last step
                if (i == pda->executionPath.size() - 1) {
                    dot_ss << "  step" << i << " [label=\"" << step.stateId << "\", shape=doublecircle];\n";
                }
                else {
                    dot_ss << "  step" << i << " [label=\"" << step.stateId << "\"];\n";
                }

                // Draw Arrow from Previous -> Current
                if (i > 0) {
                    std::string label;

                    // Input
                    label += (step.inputRaw == '\0' ? "&epsilon;" : std::string(1, step.inputRaw));
                    label += ", ";

                    // Pop
                    label += (step.popRaw == '\0' ? "&epsilon;" : std::string(1, step.popRaw));

                    // Arrow + Push
                    label += " -> ";
                    label += (step.pushRaw.empty() ? "&epsilon;" : step.pushRaw);

                    dot_ss << "  step" << (i - 1) << " -> step" << i
                        << " [label=\"" << label << "\"];\n";
                }
            }
            dot_ss << "}\n";
        }
        // MODE B: Fallback (Static Diagram) if rejected
        else {
			return "digraph G {}";
        }
        return dot_ss.str();
    }

    bool GenerateGraphvizImage(const std::string& dot_string, const std::string& image_path, std::string& out_error_message, std::string& out_fallback_text) {
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

}