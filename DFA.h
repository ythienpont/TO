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

    // Returnt de state waar je eindigt bij het ingeven van de string
    State* pad(std::string theString);

    // Minimize DFA volgens het Table Filling Algortime
    DFA minimize();

    // Print TFA tabel
    void printTable();

    // Ga equivalentie na
    bool operator==(DFA dfa2);

    std::vector<std::string> findWords(std:: string theString);
    std::vector<std::string> autocorrect1(std::string theString);
};

#endif //DFA_H
