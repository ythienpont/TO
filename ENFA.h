#include "NFA.h"
#include "DFA.h"

class ENFA : public NFA {
public:
    using NFA::NFA;

    // Geeft informatie over de eNFA
    void printStats();

    // Functie om van een eNFA naar een NFA te gaan, gebruiken we bij MSSC
    NFA toNFA();

    // Converteren naar een DFA via modified subset construction
    DFA toDFA();
};
