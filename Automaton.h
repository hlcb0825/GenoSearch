#pragma once

#include <string>
#include <vector>
#include <map>
#include <set>
#include <stack>
#include <memory>       // For std::unique_ptr
#include <iostream>
#include <sstream>      // For std::stringstream
#include <iomanip>      // For std::setw

 // ====================================================
 // GLOBAL STATE COUNTER (EXTERN)
 // This prevents "multiple definition" errors.
 // The actual variable is created in automaton_logic.cpp
 // ====================================================
extern int g_stateIdCounter;

// Epsilon character
const char EPSILON = '\0';    // Deletions
const char SUB_WILDCARD = '*'; // Substitutions (any char)
const char INS_WILDCARD = '+'; // Insertions (any char)

/**
 * @class State
 * @brief Represents a single state in an NFA.
 */
class State {
public:
    int id;
    bool isAccepting;
    std::map<char, std::vector<State*> > transitions;

    // USES THE GLOBAL COUNTER
    State() : id(g_stateIdCounter++), isAccepting(false) {}

    void addTransition(char input, State* nextState) {
        transitions[input].push_back(nextState);
    }
};

/**
 * @class NFA
 * @brief Represents a Nondeterministic Finite Automaton.
 */
class NFA {
public:
    State* startState;
    std::vector<State*> allStates;

    NFA() {
        startState = newState();
    }

    ~NFA() {
        for (size_t i = 0; i < allStates.size(); ++i) {
            delete allStates[i];
        }
    }

    State* newState() {
        State* s = new State();
        allStates.push_back(s);
        return s;
    }
};

/**
 * @class DFA
 * @brief Represents a Deterministic Finite Automaton.
 */
class DFA {
public:
    int startStateId;
    std::set<int> acceptingStateIds;
    std::map<int, std::map<char, int> > transitions;
    std::map<int, std::set<State*> > dfaStateToNFAStates;

    DFA() : startStateId(0) {}
};

/**
 * @class PDA
 * @brief Represents a Pushdown Automaton.
 */
class PDA {
public:
    std::stack<char> stack;
    std::stringstream viz_stream;
    bool didAccept;
    char stackStartSymbol;

    PDA(char startSymbol = 'Z') : stackStartSymbol(startSymbol), didAccept(false) {
        stack.push(stackStartSymbol);
    }

    std::string getStackString() {
        std::stack<char> temp = stack;
        std::string s = "";
        if (temp.empty()) return "(Empty)";
        while (!temp.empty()) {
            s = temp.top() + s;
            temp.pop();
        }
        return s;
    }

    
};