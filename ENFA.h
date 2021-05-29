#include "NFA.h"
#include "DFA.h"

class ENFAState : public NFAState {
public:
    using NFAState::NFAState; //Before C++11: NFAState(const std::string &name) : State(name);

};

class ENFA : public NFA {
public:
    using NFA::NFA;
    virtual ~ENFA();

    // Geeft informatie over de eNFA
    void printStats();

    // Functie om van een eNFA naar een NFA te gaan, gebruiken we bij MSSC
    NFA toNFA();

    // Converteren naar een DFA via modified subset construction
    DFA toDFA();


};
