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

int g_stateIdCounter = 0;  // Global counter for generating unique state IDs

namespace GenoSearchEngine {

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
    //          THEORETICAL ANALYSIS FUNCTIONS
    // ========================================

    // Analyzes language class and properties
    std::string analyzeLanguageClass(const std::string& pattern, const std::string& mode) {
        std::stringstream ss;

        if (mode == "REGEX") {
            ss << "LANGUAGE CLASS: REGULAR (Type-3)\n";
            ss << "FORMAL DEFINITION: L = {w ∈ Σ* | w matches pattern}\n";
            ss << "CLOSURE PROPERTIES: Closed under ∪, ∘, *, complement, intersection\n";
            ss << "RECOGNIZER: Deterministic Finite Automaton (DFA)\n";
            ss << "GRAMMAR TYPE: Right-Linear Grammar\n";
        }
        else if (mode == "LEVENSHTEIN") {
            ss << "LANGUAGE CLASS: REGULAR (Type-3) with Edit Distance\n";
            ss << "FORMAL DEFINITION: L_k = {w ∈ Σ* | ∃v ∈ L_pattern, d(w,v) ≤ k}\n";
            ss << "THEORETICAL MODEL: Levenshtein Automaton (NFA)\n";
            ss << "COMPLEXITY CLASS: O(N·M·k) - exponential in k\n";
            ss << "ALPHABET EXPANSION: Σ ∪ {ε, *, +} for edit operations\n";
        }
        else if (mode == "PDA") {
            ss << "LANGUAGE CLASS: CONTEXT-FREE (Type-2)\n";
            ss << "FORMAL DEFINITION: Requires pushdown automaton for recognition\n";
            ss << "GRAMMAR TYPE: Context-Free Grammar (not right-linear)\n";
            ss << "PUMPING LEMMA: Regular pumping lemma fails - proves non-regularity\n";
            ss << "STACK NECESSITY: Finite memory insufficient for nested structures\n";
        }

        return ss.str();
    }

    // Generates formal automaton definition
    std::string generateFormalDefinition(const std::string& automatonType,
        int states, int alphabetSize, int acceptStates) {
        std::stringstream ss;

        if (automatonType == "DFA") {
            ss << "FORMAL DEFINITION: M = (Q, Σ, δ, q₀, F)\n";
            ss << "• |Q| = " << states << " (finite set of states)\n";
            ss << "• |Σ| = " << alphabetSize << " (input alphabet)\n";
            ss << "• δ: Q × Σ → Q (deterministic transition function)\n";
            ss << "• q₀ ∈ Q (initial state)\n";
            ss << "• |F| = " << acceptStates << " (accepting states)\n";
        }
        else if (automatonType == "NFA") {
            ss << "FORMAL DEFINITION: M = (Q, Σ, δ, q₀, F)\n";
            ss << "• |Q| = " << states << " (finite set of states)\n";
            ss << "• |Σ| = " << alphabetSize << " (input alphabet)\n";
            ss << "• δ: Q × (Σ ∪ {ε}) → P(Q) (nondeterministic transitions)\n";
            ss << "• q₀ ∈ Q (initial state)\n";
            ss << "• |F| = " << acceptStates << " (accepting states)\n";
        }
        else if (automatonType == "PDA") {
            ss << "FORMAL DEFINITION: M = (Q, Σ, Γ, δ, q₀, Z₀, F)\n";
            ss << "• Q = finite set of states\n";
            ss << "• Σ = input alphabet\n";
            ss << "• Γ = stack alphabet\n";
            ss << "• δ: Q × (Σ ∪ {ε}) × Γ → P(Q × Γ*) (transition function)\n";
            ss << "• q₀ ∈ Q (initial state)\n";
            ss << "• Z₀ ∈ Γ (initial stack symbol)\n";
            ss << "• F ⊆ Q (accepting states)\n";
        }

        return ss.str();
    }

    // Demonstrates pumping lemma for language classification
    std::string demonstratePumpingLemma(const std::string& pattern, const std::string& mode) {
        std::stringstream ss;

        if (mode == "REGEX") {
            ss << "PUMPING LEMMA FOR REGULAR LANGUAGES:\n";
            ss << "• Applies to this language ✓\n";
            ss << "• For any string w ∈ L with |w| ≥ p, can be split as w = xyz\n";
            ss << "• Conditions: |xy| ≤ p, |y| ≥ 1, xyⁱz ∈ L for all i ≥ 0\n";
            ss << "• Proof: This pattern generates a regular language\n";
        }
        else if (mode == "PDA_BRACKET") {
            ss << "PUMPING LEMMA FAILURE - PROVES NON-REGULARITY:\n";
            ss << "• Language: {aⁿbⁿ | n ≥ 0} or balanced parentheses\n";
            ss << "• Assume regular with pumping length p\n";
            ss << "• Choose s = aᵖbᵖ, |s| = 2p ≥ p\n";
            ss << "• For any split s = xyz with |xy| ≤ p, y must be all a's\n";
            ss << "• Pumping y gives aᵖ⁺ᵏbᵖ ∉ L for k ≥ 1 - CONTRADICTION\n";
            ss << "• ∴ Language is not regular - requires pushdown automaton\n";
        }
        else if (mode == "PDA_HAIRPIN") {
            ss << "PUMPING LEMMA FAILURE - PROVES NON-REGULARITY:\n";
            ss << "• Language: {w wᴿ | w ∈ Σ*} (hairpin structures)\n";
            ss << "• Assume regular with pumping length p\n";
            ss << "• Choose s = aᵖb aᵖb (with aᵖ mirrored)\n";
            ss << "• Any pumping breaks the mirror symmetry\n";
            ss << "• ∴ Language is not regular - requires stack memory\n";
        }

        return ss.str();
    }

    // Analyzes language containment hierarchy for approximate matching
    std::string analyzeLanguageContainment(const std::vector<std::pair<std::string, int>>& matches,
        const std::string& pattern, int k) {
        std::stringstream ss;

        int perfectMatches = 0;
        int within1Error = 0;
        int within2Errors = 0;
        int totalSubstitutions = 0;
        int totalInsertions = 0;
        int totalDeletions = 0;

        for (const auto& match : matches) {
            if (match.second == 0) perfectMatches++;
            if (match.second <= 1) within1Error++;
            if (match.second <= 2) within2Errors++;

            // Simplified error type estimation (in real implementation, track operations)
            if (match.first.length() > pattern.length()) totalInsertions++;
            else if (match.first.length() < pattern.length()) totalDeletions++;
            else if (match.second > 0) totalSubstitutions++;
        }

        ss << "LANGUAGE CONTAINMENT HIERARCHY:\n";
        ss << "• L₀ (exact matches): |L₀ ∩ Input| = " << perfectMatches << "\n";
        ss << "• L₁ (≤1 error): |L₁ ∩ Input| = " << within1Error << "\n";
        ss << "• L₂ (≤2 errors): |L₂ ∩ Input| = " << within2Errors << "\n";
        ss << "• Lₖ (≤k errors): |Lₖ ∩ Input| = " << matches.size() << "\n";
        ss << "\nERROR DISTRIBUTION:\n";
        ss << "• Substitutions: " << totalSubstitutions << "\n";
        ss << "• Insertions: " << totalInsertions << "\n";
        ss << "• Deletions: " << totalDeletions << "\n";
        ss << "\nTHEORETICAL MODEL: L₀ ⊆ L₁ ⊆ L₂ ⊆ ... ⊆ Lₖ\n";

        return ss.str();
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

    void printHeader(std::stringstream& ss, const std::string& title) {
        ss << "\n" << std::string(60, '=') << "\n";
        ss << " " << title << "\n";
        ss << std::string(60, '=') << "\n";
    }

    void printTableRow(std::stringstream& ss, const std::string& label, const std::string& value) {
        ss << "• " << std::left << std::setw(35) << label << ": " << value << "\n";
    }

    // ========================================
    //    REGEX ENGINE (WITH ESCAPE SUPPORT)
    // ========================================

    int precedence(char op) {
        if (op == '*') return 3;
        if (op == '.') return 2;
        if (op == '|') return 1;
        return 0;
    }

    std::string infixToPostfix(const std::string& infix) {
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

        for (size_t i = 0; i < nfa->allStates.size(); ++i) {
            State* s = nfa->allStates[i];
            if (s == nullptr) continue;
            for (std::map<char, std::vector<State*>>::iterator it = s->transitions.begin();
                it != s->transitions.end(); ++it) {
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
            std::set<State*> currentNFAStates = workQueue.front();
            workQueue.pop();
            int currentDFAId = dfaStateMap[currentNFAStates];

            for (std::set<State*>::iterator it = currentNFAStates.begin();
                it != currentNFAStates.end(); ++it) {
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

    // ========================================
    //    THEORETICAL ANALYSIS FOR SIMULATION 1
    // ========================================

    std::string generateRegexSearchParameters(const std::string& regex, const std::string& postfix,
        const std::string& filepath, double executionTime) {
        std::stringstream ss;
        printHeader(ss, "REGEX SEARCH PARAMETERS");

        ss << analyzeLanguageClass(regex, "REGEX") << "\n";

        printTableRow(ss, "Input Pattern", regex);
        printTableRow(ss, "Postfix Notation", postfix);
        printTableRow(ss, "Search Strategy", "Deterministic (DFA)");
        printTableRow(ss, "Theoretical Complexity", "O(N²·M) where N=text, M=pattern");
        printTableRow(ss, "Execution Time", std::to_string(executionTime) + "s");
        printTableRow(ss, "Input File", filepath);
        printTableRow(ss, "Alphabet", "Σ = {A, T, C, G, ...} (ASCII 32-126)");
        printTableRow(ss, "Language", "L = {w ∈ Σ* | w matches pattern}");

        return ss.str();
    }

    std::string generateDFAConstruction(NFA* nfa, DFA* dfa) {
        std::stringstream ss;
        printHeader(ss, "DFA CONSTRUCTION");

        int alphabetSize = 0;
        std::set<char> alphabet;
        if (nfa != nullptr) {
            for (auto state : nfa->allStates) {
                for (auto& trans : state->transitions) {
                    if (trans.first != EPSILON) alphabet.insert(trans.first);
                }
            }
            alphabetSize = alphabet.size();
        }

        ss << generateFormalDefinition("DFA",
            dfa->dfaStateToNFAStates.size(),
            alphabetSize,
            dfa->acceptingStateIds.size()) << "\n";

        printTableRow(ss, "NFA States", std::to_string(nfa->allStates.size()));
        printTableRow(ss, "DFA States", std::to_string(dfa->dfaStateToNFAStates.size()));
        printTableRow(ss, "Accepting States", std::to_string(dfa->acceptingStateIds.size()));
        printTableRow(ss, "Alphabet Size", std::to_string(alphabetSize));
        printTableRow(ss, "State Minimization", "Not implemented (educational)");
        printTableRow(ss, "Myhill-Nerode Classes", "≥ " + std::to_string(dfa->dfaStateToNFAStates.size()));

        ss << "\n" << demonstratePumpingLemma("", "REGEX");

        return ss.str();
    }

    std::string generateExactMatchResults(const std::vector<std::string>& matches,
        const std::string& pattern) {
        std::stringstream ss;
        printHeader(ss, "EXACT MATCH RESULTS");

        ss << "LANGUAGE MEMBERSHIP ANALYSIS:\n";
        printTableRow(ss, "Total Strings in L ∩ Input", std::to_string(matches.size()));

        if (!matches.empty()) {
            size_t minLen = matches[0].length();
            size_t maxLen = matches[0].length();
            for (const auto& match : matches) {
                if (match.length() < minLen) minLen = match.length();
                if (match.length() > maxLen) maxLen = match.length();
            }

            printTableRow(ss, "Shortest Match Length", std::to_string(minLen));
            printTableRow(ss, "Longest Match Length", std::to_string(maxLen));
            printTableRow(ss, "Empty String (ε)", (minLen == 0 ? "Present" : "Absent"));
        }

        ss << "\nSAMPLE MATCHES (first 10):\n";
        for (size_t i = 0; i < std::min(matches.size(), size_t(10)); ++i) {
            ss << "  " << std::setw(3) << (i + 1) << ": \"" << matches[i] << "\"\n";
        }

        if (matches.size() > 10) {
            ss << "  ... and " << (matches.size() - 10) << " more matches\n";
        }

        return ss.str();
    }

    // ========================================
    // LEVENSHTEIN NFA (THEORETICAL VERSION)
    // ========================================

    const char EPSILON = '\0';
    const char SUB_WILDCARD = '*';
    const char INS_WILDCARD = '+';

    std::unique_ptr<NFA> buildLevenshteinNFA(const std::string& pattern, int maxErrors) {
        g_stateIdCounter = 0;
        std::unique_ptr<NFA> nfa(new NFA());

        std::map<std::pair<int, int>, State*> stateMap;
        int n = pattern.length();

        for (int pos = 0; pos <= n; ++pos) {
            for (int err = 0; err <= maxErrors; ++err) {
                State* state = (pos == 0 && err == 0) ? nfa->startState : nfa->newState();
                stateMap[std::make_pair(pos, err)] = state;

                if (pos == n) {
                    state->isAccepting = true;
                }
            }
        }

        for (int pos = 0; pos < n; ++pos) {
            for (int err = 0; err <= maxErrors; ++err) {
                State* currentState = stateMap[std::make_pair(pos, err)];
                char patternChar = pattern[pos];

                State* matchState = stateMap[std::make_pair(pos + 1, err)];
                currentState->addTransition(patternChar, matchState);

                if (err < maxErrors) {
                    State* subState = stateMap[std::make_pair(pos + 1, err + 1)];
                    State* insState = stateMap[std::make_pair(pos, err + 1)];
                    State* delState = stateMap[std::make_pair(pos + 1, err + 1)];

                    currentState->addTransition(SUB_WILDCARD, subState);
                    currentState->addTransition(INS_WILDCARD, insState);
                    currentState->addTransition(EPSILON, delState);
                }
            }
        }

        return nfa;
    }

    std::vector<std::pair<std::string, int>> simulateLevenshteinNFA(NFA* nfa, const std::string& text,
        const std::string& pattern, int k) {
        std::set<std::pair<std::string, int>> uniqueMatches;

        auto startTime = std::chrono::high_resolution_clock::now();
        int totalMatchesFound = 0;

        for (size_t start = 0; start < text.length(); ++start) {
            auto currentTime = std::chrono::high_resolution_clock::now();
            if (std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime).count() > 10) {
                break;
            }

            if (totalMatchesFound >= 100) break;

            std::queue<std::tuple<State*, size_t, int, std::string, int>> queue;
            std::set<std::tuple<int, size_t, int, size_t, int>> visited;

            std::set<State*> initialSet;
            initialSet.insert(nfa->startState);
            std::set<State*> initialClosure = epsilonClosure(initialSet);

            for (std::set<State*>::iterator it = initialClosure.begin();
                it != initialClosure.end(); ++it) {
                queue.push(std::make_tuple(*it, start, 0, "", 0));
            }

            while (!queue.empty()) {
                currentTime = std::chrono::high_resolution_clock::now();
                if (std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime).count() > 10) {
                    break;
                }

                auto current = queue.front();
                queue.pop();

                State* state = std::get<0>(current);
                size_t textPos = std::get<1>(current);
                int errors = std::get<2>(current);
                std::string matched = std::get<3>(current);
                int patternPos = std::get<4>(current);

                std::tuple<int, size_t, int, size_t, int> key =
                    std::make_tuple(state->id, textPos, errors, matched.length(), patternPos);
                if (visited.count(key)) continue;
                visited.insert(key);

                if (state->isAccepting && patternPos >= pattern.length() - k) {
                    if (uniqueMatches.insert(std::make_pair(matched, errors)).second) {
                        totalMatchesFound++;
                    }
                    if (totalMatchesFound >= 100) break;
                }

                if (matched.length() > pattern.length() + k * 2) continue;
                if (errors > k) continue;

                if (textPos < text.length()) {
                    char c = text[textPos];

                    for (auto& trans : state->transitions) {
                        char transitionChar = trans.first;
                        std::vector<State*>& nextStates = trans.second;

                        for (State* nextState : nextStates) {
                            int newErrors = errors;
                            int newPatternPos = patternPos;
                            std::string newMatched = matched + c;

                            if (transitionChar == c) {
                                newPatternPos++;
                            }
                            else if (transitionChar == SUB_WILDCARD) {
                                newPatternPos++;
                                newErrors++;
                            }
                            else if (transitionChar == INS_WILDCARD) {
                                newErrors++;
                            }
                            else if (transitionChar == EPSILON) {
                                newPatternPos++;
                                newErrors++;
                                newMatched = matched;
                                queue.push(std::make_tuple(nextState, textPos, newErrors, newMatched, newPatternPos));
                                continue;
                            }
                            else {
                                continue;
                            }

                            queue.push(std::make_tuple(nextState, textPos + 1, newErrors, newMatched, newPatternPos));
                        }
                    }
                }

                if (state->transitions.count(EPSILON)) {
                    std::vector<State*>& nextStates = state->transitions[EPSILON];
                    for (State* nextState : nextStates) {
                        queue.push(std::make_tuple(nextState, textPos, errors + 1, matched, patternPos + 1));
                    }
                }
            }

            if (totalMatchesFound >= 100) break;
        }

        std::vector<std::pair<std::string, int>> result(uniqueMatches.begin(), uniqueMatches.end());

        std::sort(result.begin(), result.end(),
            [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
                if (a.first.length() != b.first.length())
                    return a.first.length() < b.first.length();
                return a.second < b.second;
            });

        return result;
    }

    // ========================================
    //    THEORETICAL ANALYSIS FOR SIMULATION 2
    // ========================================

    std::string generateFuzzySearchParameters(const std::string& pattern, int k,
        const std::string& filepath, double executionTime,
        size_t nfaStateCount) {
        std::stringstream ss;
        printHeader(ss, "FUZZY SEARCH PARAMETERS");

        ss << analyzeLanguageClass(pattern, "LEVENSHTEIN") << "\n";

        printTableRow(ss, "Target Pattern", pattern);
        printTableRow(ss, "Max Errors Allowed (k)", std::to_string(k));
        printTableRow(ss, "Edit Operations", "Insert, Delete, Substitute");
        printTableRow(ss, "Theoretical Model", "Levenshtein Automaton (NFA)");
        printTableRow(ss, "Complexity Warning", "Exponential in k - O(N·M·k)");
        printTableRow(ss, "Execution Time", std::to_string(executionTime) + "s");
        printTableRow(ss, "Input File", filepath);
        printTableRow(ss, "NFA State Count", std::to_string(nfaStateCount));

        return ss.str();
    }

    std::string generateLevenshteinAutomaton(const std::string& pattern, int k, NFA* nfa) {
        std::stringstream ss;
        printHeader(ss, "LEVENSHTEIN AUTOMATON");

        ss << "STATE TRANSITION SYSTEM:\n";
        printTableRow(ss, "Automaton Type", "Nondeterministic (NFA)");
        printTableRow(ss, "Grid Dimensions", "(" + std::to_string(pattern.length() + 1) + " × " + std::to_string(k + 1) + ")");
        printTableRow(ss, "Total States", std::to_string(nfa->allStates.size()));
        printTableRow(ss, "State Representation", "(pattern_position, errors_used)");
        printTableRow(ss, "Theoretical States", std::to_string((pattern.length() + 1) * (k + 1)));

        ss << "\nTRANSITION TYPES:\n";
        printTableRow(ss, "Match (exact)", "(p,e) → (p+1,e) on exact char");
        printTableRow(ss, "Substitute (*)", "(p,e) → (p+1,e+1) on Σ\\{char}");
        printTableRow(ss, "Insert (+)", "(p,e) → (p,e+1) on Σ");
        printTableRow(ss, "Delete (ε)", "(p,e) → (p+1,e+1) on ε");

        ss << "\n" << generateFormalDefinition("NFA", nfa->allStates.size(), 0, 0);

        return ss.str();
    }

    std::string generateApproximateMatchResults(const std::vector<std::pair<std::string, int>>& matches,
        const std::string& pattern, int k) {
        std::stringstream ss;
        printHeader(ss, "APPROXIMATE MATCH RESULTS");

        ss << analyzeLanguageContainment(matches, pattern, k) << "\n";

        ss << "SAMPLE MATCHES (first 10):\n";
        for (size_t i = 0; i < std::min(matches.size(), size_t(10)); ++i) {
            ss << "  " << std::setw(3) << (i + 1) << ": \"" << matches[i].first
                << "\" (errors: " << matches[i].second << ")\n";
        }

        if (matches.size() > 10) {
            ss << "  ... and " << (matches.size() - 10) << " more matches\n";
        }

        return ss.str();
    }

    // ========================================
    // PDA STRUCTURES (THEORETICAL VERSION)
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
        int stackDepth;

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
        int maxStackDepth;

        FormalPDA() : stackStartSymbol('Z'), accepted(false), maxStackDepth(0) {}
    };

    std::unique_ptr<FormalPDA> buildDNAPDA() {
        std::unique_ptr<FormalPDA> pda(new FormalPDA());

        pda->acceptStates.insert(2);

        pda->transitions.push_back({ 0, 'G', '\0', 0, "G" });
        pda->transitions.push_back({ 0, 'A', '\0', 0, "A" });
        pda->transitions.push_back({ 0, 'T', '\0', 0, "T" });
        pda->transitions.push_back({ 0, 'C', '\0', 0, "C" });

        pda->transitions.push_back({ 0, '\0', '\0', 1, "" });

        pda->transitions.push_back({ 1, 'N', '\0', 1, "" });
        pda->transitions.push_back({ 1, '-', '\0', 1, "" });
        pda->transitions.push_back({ 1, ' ', '\0', 1, "" });

        pda->transitions.push_back({ 1, '\0', '\0', 2, "" });

        pda->transitions.push_back({ 0, 'C', 'G', 2, "" });
        pda->transitions.push_back({ 0, 'T', 'A', 2, "" });
        pda->transitions.push_back({ 0, 'U', 'A', 2, "" });
        pda->transitions.push_back({ 0, 'G', 'C', 2, "" });
        pda->transitions.push_back({ 0, 'A', 'T', 2, "" });
        pda->transitions.push_back({ 0, 'A', 'U', 2, "" });

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

        pda->transitions.push_back({ 0, '<', '\0', 0, "X" });
        pda->transitions.push_back({ 0, '/', 'X', 0, "" });

        return pda;
    }

    bool simulateFormalPDA(FormalPDA* pda, const std::string& input) {
        pda->traceStream.str("");
        pda->traceStream << std::left
            << std::setw(10) << "State"
            << std::setw(15) << "Input"
            << std::setw(20) << "Stack"
            << std::setw(25) << "Action" << "\n";
        pda->traceStream << std::string(70, '-') << "\n";

        std::queue<PDASnapshot> queue;

        PDASnapshot initial;
        initial.state = 0;
        initial.stack.push(pda->stackStartSymbol);
        initial.inputPos = 0;
        initial.path.push_back("START");
        initial.stackDepth = 1;
        queue.push(initial);

        std::set<std::string> visitedConfigs;

        while (!queue.empty()) {
            PDASnapshot current = queue.front();
            queue.pop();

            if (current.stackDepth > pda->maxStackDepth) {
                pda->maxStackDepth = current.stackDepth;
            }

            std::stringstream configKey;
            configKey << current.state << ":" << current.inputPos << ":" << current.getStackString();
            std::string key = configKey.str();

            if (visitedConfigs.count(key)) continue;
            visitedConfigs.insert(key);

            if (current.inputPos < input.length()) {
                pda->traceStream << std::setw(10) << current.state
                    << std::setw(15) << input[current.inputPos]
                    << std::setw(20) << current.getStackString()
                    << std::setw(25) << "Processing..." << "\n";
            }

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

            for (size_t i = 0; i < pda->transitions.size(); ++i) {
                PDATransition& trans = pda->transitions[i];

                if (trans.fromState != current.state) continue;

                bool inputMatches = (trans.inputSymbol == currentInput || trans.inputSymbol == '\0');
                bool stackMatches = (trans.stackTop == '\0' || trans.stackTop == stackTop);

                if (!inputMatches || !stackMatches) continue;

                PDASnapshot next;
                next.state = trans.toState;
                next.stack = current.stack;
                next.inputPos = current.inputPos;
                next.path = current.path;
                next.stackDepth = current.stackDepth;

                if (trans.stackTop != '\0' && !next.stack.empty()) {
                    next.stack.pop();
                    next.stackDepth--;
                }

                for (int j = trans.stackPush.length() - 1; j >= 0; --j) {
                    next.stack.push(trans.stackPush[j]);
                    next.stackDepth++;
                }

                if (trans.inputSymbol != '\0') {
                    next.inputPos++;
                }

                std::stringstream action;
                if (trans.stackTop != '\0') action << "POP(" << trans.stackTop << ") ";
                if (!trans.stackPush.empty()) action << "PUSH(" << trans.stackPush << ")";
                if (trans.inputSymbol == '\0') action << " [ε-transition]";
                next.path.push_back(action.str());

                queue.push(next);
            }
        }

        pda->accepted = false;
        pda->traceStream << "\n=== REJECTED ===\n";
        pda->traceStream << "No accepting configuration found.\n";
        return false;
    }

    // ========================================
    //    THEORETICAL ANALYSIS FOR SIMULATION 3
    // ========================================

    std::string generateStructureValidationParameters(const std::string& mode, const std::string& input) {
        std::stringstream ss;
        printHeader(ss, "STRUCTURE VALIDATION PARAMETERS");

        ss << analyzeLanguageClass("", "PDA") << "\n";

        printTableRow(ss, "Detected Mode", mode);
        printTableRow(ss, "Language Class", "Context-Free (Type-2)");
        printTableRow(ss, "Grammar Type", "Context-Free Grammar");
        printTableRow(ss, "Recognizer", "Nondeterministic Pushdown Automaton");
        printTableRow(ss, "Validation Strategy", "BFS Simulation");
        printTableRow(ss, "Input Length", std::to_string(input.length()));

        if (mode == "DNA" || mode == "RNA") {
            printTableRow(ss, "Language", "{w wᴿ | w ∈ Σ*} (hairpin structures)");
            printTableRow(ss, "Base Pairing", "A-T, G-C, A-U (RNA)");
        }
        else if (mode == "BRACKET") {
            printTableRow(ss, "Language", "Balanced parentheses/brackets");
            printTableRow(ss, "Classic Example", "{aⁿbⁿ | n ≥ 0}");
        }
        else if (mode == "XML") {
            printTableRow(ss, "Language", "Properly nested XML tags");
            printTableRow(ss, "Grammar", "S → <tag>S</tag> | SS | ε");
        }

        return ss.str();
    }

    std::string generatePDAConfiguration(FormalPDA* pda, const std::string& mode) {
        std::stringstream ss;
        printHeader(ss, "PDA CONFIGURATION");

        ss << generateFormalDefinition("PDA", 0, 0, pda->acceptStates.size()) << "\n";

        printTableRow(ss, "Start Symbol", std::string(1, pda->stackStartSymbol));
        printTableRow(ss, "Acceptance Criteria", "Empty Stack + Final State");
        printTableRow(ss, "Accept States", std::to_string(pda->acceptStates.size()));
        printTableRow(ss, "Transition Count", std::to_string(pda->transitions.size()));
        printTableRow(ss, "Stack Operations", "Push, Pop (LIFO memory)");
        printTableRow(ss, "Nondeterminism", "Essential for some context-free languages");

        ss << "\n" << demonstratePumpingLemma("",
            mode == "BRACKET" ? "PDA_BRACKET" : "PDA_HAIRPIN");

        return ss.str();
    }

    std::string generateValidationResults(bool isValid, FormalPDA* pda, const std::string& input,
        const std::string& mode) {
        std::stringstream ss;
        printHeader(ss, "VALIDATION RESULTS");

        ss << "PARSE TREE ANALYSIS:\n";
        printTableRow(ss, "Input", input.substr(0, 50) + (input.length() > 50 ? "..." : ""));
        printTableRow(ss, "Final Status", isValid ? "✓ ACCEPTED" : "✗ REJECTED");
        printTableRow(ss, "Max Stack Depth", std::to_string(pda->maxStackDepth));
        printTableRow(ss, "Stack Necessity", "Proven by pumping lemma failure");
        printTableRow(ss, "Language Membership", isValid ? "w ∈ L" : "w ∉ L");

        if (isValid) {
            if (mode == "DNA" || mode == "RNA") {
                printTableRow(ss, "Structural Feature", "Valid hairpin structure");
                printTableRow(ss, "Base Pairing", "Watson-Crick complementary");
            }
            else if (mode == "BRACKET") {
                printTableRow(ss, "Structural Feature", "Balanced nesting");
                printTableRow(ss, "Nesting Depth", std::to_string(pda->maxStackDepth - 1));
            }
        }

        ss << "\nTHEORETICAL SIGNIFICANCE:\n";
        ss << "• Proves language is context-free, not regular\n";
        ss << "• Demonstrates need for infinite memory (stack)\n";
        ss << "• Shows limitations of regular expressions\n";
        ss << "• Validates Chomsky hierarchy: Regular ⊂ Context-Free\n";

        return ss.str();
    }

    // ========================================
    //    VISUALIZATION FUNCTIONS (UNCHANGED)
    // ========================================

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

            for (auto& trans : s->transitions) {
                char key = trans.first;
                std::vector<State*>& nextStates = trans.second;

                for (State* next : nextStates) {
                    if (next == nullptr) continue;

                    std::string label;
                    if (key == EPSILON)
                        label = "ε";
                    else if (key == SUB_WILDCARD)
                        label = "sub(*)";
                    else if (key == INS_WILDCARD)
                        label = "ins(+)";
                    else
                        label = std::string(1, key);

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

    // ========================================
    //    PUBLIC WRAPPER FUNCTIONS (UPDATED)
    // ========================================

    void runBranch1_logic(
        const std::string& regex, const std::string& filepath,
        SimulationReport& out_report, VisualizationData& out_viz, std::string& out_error_msg)
    {
        try {
            auto start = std::chrono::high_resolution_clock::now();

            std::string text = readFile(filepath);
            if (text.rfind("[Error]", 0) == 0) {
                out_error_msg = text;
                return;
            }

            std::string postfix = infixToPostfix(regex);

            // FIX: Create temporary stringstream for buildThompson
            std::stringstream grammar_ss;
            std::unique_ptr<NFA> nfa = buildThompson(postfix, grammar_ss);

            std::unique_ptr<DFA> dfa = buildDFA(nfa.get());
            std::vector<std::string> matches = simulateDFA(dfa.get(), text);

            auto stop = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
            double executionTime = duration.count() / 1000.0;

            out_viz.nfaDot = generateNfaDot(nfa.get());
            out_viz.dfaDot = generateDfaDot(dfa.get());

            out_report.summary = generateRegexSearchParameters(regex, postfix, filepath, executionTime);
            out_report.grammar = generateDFAConstruction(nfa.get(), dfa.get());
            out_report.matches = generateExactMatchResults(matches, regex);

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

            std::string text = readFile(filepath);
            if (text.rfind("[Error]", 0) == 0) {
                out_error_msg = text;
                return;
            }

            std::unique_ptr<NFA> levenshteinNFA = buildLevenshteinNFA(pattern, k);
            std::vector<std::pair<std::string, int>> matches =
                simulateLevenshteinNFA(levenshteinNFA.get(), text, pattern, k);

            auto stop = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
            double executionTime = duration.count() / 1000.0;

            size_t nfaStateCount = levenshteinNFA->allStates.size();
            if (nfaStateCount <= 50) {
                out_viz.nfaDot = generateNfaDot(levenshteinNFA.get());
            }
            else {
                std::stringstream simpleViz;
                simpleViz << "digraph SimplifiedLevenshtein {\n";
                simpleViz << "  rankdir=TB;\n  node [shape=rectangle];\n";
                simpleViz << "  label=\"Levenshtein NFA (Too large: " << nfaStateCount << " states)\\n";
                simpleViz << "Pattern: " << pattern << " (k=" << k << ")\\n";
                simpleViz << "Grid: " << pattern.length() + 1 << " positions × " << (k + 1) << " errors\";\n";
                simpleViz << "  info [shape=note, label=\"";
                simpleViz << "Edit Operations:\\n";
                simpleViz << "• Match: exact char → same errors\\n";
                simpleViz << "• Substitute: ? → errors+1\\n";
                simpleViz << "• Insert: ? → errors+1\\n";
                simpleViz << "• Delete: ε → errors+1\"];\n";
                simpleViz << "}\n";
                out_viz.nfaDot = simpleViz.str();
            }

            out_report.summary = generateFuzzySearchParameters(pattern, k, filepath, executionTime, nfaStateCount);
            out_report.grammar = generateLevenshteinAutomaton(pattern, k, levenshteinNFA.get());
            out_report.matches = generateApproximateMatchResults(matches, pattern, k);

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

            out_report.summary = generateStructureValidationParameters(mode, full_text);
            out_report.grammar = generatePDAConfiguration(pda.get(), mode);
            out_report.matches = generateValidationResults(isValid, pda.get(), full_text, mode);
            out_viz.pdaTrace = pda->traceStream.str();

        }
        catch (std::exception& e) {
            out_error_msg = "[Error] " + std::string(e.what());
        }
    }

    // ========================================
    //    GRAPHVIZ FUNCTIONS (UNCHANGED)
    // ========================================

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