#ifndef NFA_H
#define NFA_H
#include "Automaton.h"
#include "DFA.h"

std::vector<std::string> getUniqueStates(std::vector<std::string> states);

class NFAState : public State {
    std::map<char, std::vector<std::string>> transitions;
public:
    using State::State; //Before C++11: NFAState(const std::string &name) : State(name);

    void addTransition(const char c, const std::string &state);
    void addTransition(const char c, const std::vector<std::string> &states);

    std::map<char, std::vector<std::string>> getTransitions() {return transitions;}

    std::vector<std::string> nextStates(const char input) {
        std::vector<std::string> theNextStates = transitions[input];

        return theNextStates;
    }
};

class NFA : public Automaton{
public:
    using Automaton::Automaton;

    //bool accepts(const std::string &theString) {return false;}
    bool accepts(const std::string &theString);

    // Subset construction algorithm converts NFA to DFA
    virtual DFA toDFA();
};

#endif //DFA_H
