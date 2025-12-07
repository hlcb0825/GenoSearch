#pragma once

#include <string>
#include <vector>
#include <map>
#include <set>
#include <stack>
#include <memory>
#include <iostream>
#include <sstream>
#include <iomanip>

// Global State Counter
extern int g_stateIdCounter;

// Constants
const char EPSILON = '\0';

/**
 * @class State
 * @brief Represents a single state in an NFA.
 */
class State {
public:
    int id;
    bool isAccepting;
    std::map<char, std::vector<State*> > transitions;

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
    char stackStartSymbol;

    PDA(char startSymbol = 'Z') : stackStartSymbol(startSymbol) {
        stack.push(stackStartSymbol);
    }
};