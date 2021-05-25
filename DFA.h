#ifndef DFA_H
#define DFA_H
#include "Automaton.h"

class DFA : public Automaton{
    std::vector<std::vector<std::string>> TFATable;
public:
    using Automaton::Automaton;

    // Constructor door product
    DFA(DFA dfa1,DFA dfa2, bool intersection);

    bool accepts(const std::string &theString) override;

    // Minimize DFA volgens het Table Filling Algortime
    DFA minimize();

    // Print TFA tabel
    void printTable();

    bool operator==(DFA dfa2);
};

#endif //DFA_H
