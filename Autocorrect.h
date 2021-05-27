
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

    void autocorrect1(DFA);

    void autocorrect2(DFA);
};


#endif //AUTOCORRECT_AUTOCORRECT_H
