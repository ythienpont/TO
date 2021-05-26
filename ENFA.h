#include "NFA.h"
#include "DFA.h"

class ENFAState : public State {
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

class ENFA : public NFA {
    std::map<char, std::vector<std::string>> transitions;
public:
    using NFA::NFA;


    // Geeft informatie over de eNFA
    void printStats();

    // Functie om van een eNFA naar een NFA te gaan, gebruiken we bij MSSC
    NFA toNFA();

    // Converteren naar een DFA via modified subset construction
    DFA toDFA();


};
