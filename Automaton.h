/*
 * Automaton.h
 * Defines the "parts" of your GenoSearch engine.
 * This is PURE C++ and has no GUI code.
 */

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

 // Use a static variable for unique state IDs
static int g_stateIdCounter = 0;

// Epsilon character (use '\0' for simplicity)
const char EPSILON = '\0';

/**
 * @class State
 * @brief Represents a single state in an NFA.
 */
class State {
public:
    int id;
    bool isAccepting;
    // Transitions: map<char, vector<State*>>
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
    std::vector<State*> allStates; // This NFA "owns" all its states

    NFA() {
        startState = newState(); // Create an initial start state
    }

    // Destructor to clean up all states
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
    // Transition table: map<from_state_id, map<char, to_state_id>>
    std::map<int, std::map<char, int> > transitions;
    // For visualization: maps a DFA state ID to the set of NFA states
    std::map<int, std::set<State*> > dfaStateToNFAStates;

    DFA() : startStateId(0) {}
};

/**
 * @class PDA
 * @brief Represents a Pushdown Automaton.
 * (This is a simple container, the logic is in automaton_logic.cpp)
 */
class PDA {
public:
    std::stack<char> stack;
    std::stringstream viz_stream; // For capturing the visualization trace
    bool didAccept;
    char stackStartSymbol;

    PDA(char startSymbol = 'Z') : stackStartSymbol(startSymbol), didAccept(false) {
        stack.push(stackStartSymbol);
    }

    // Helper function to get a string representation of the stack
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