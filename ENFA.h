#include "NFA.h"
#include "DFA.h"

class ENFAState : public NFAState {
    std::map<char, std::vector<std::string>> transitions;
public:
    using NFAState::NFAState; //Before C++11: NFAState(const std::string &name) : State(name);

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
