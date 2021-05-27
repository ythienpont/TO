
#ifndef AUTOCORRECT_AUTOCORRECT_H
#define AUTOCORRECT_AUTOCORRECT_H

#include "DFA.h"
#include "RE.h"
#include <vector>

class Autocorrect {
    vector<RE> listRegex;
    DFA mainDFA = DFA("");
public:
    Autocorrect()= default;;

    void inlezen();

    void autocorrect1(const string& theString); // print de verbeterde versies van een string
    void autocorrect2(const string& theString);
    void generateWord(); // genereert een willekeurig woord die door de automaat geaccepteerd wordt
};


#endif //AUTOCORRECT_AUTOCORRECT_H
