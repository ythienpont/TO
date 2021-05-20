//
// Created by Alperen on 25/03/2021.
//

#ifndef TA1_13_02_NFA_H
#define TA1_13_02_NFA_H

#include <iostream>
#include "DFA.h"
using namespace std;

class NFA: public DFA {
public:
    bool bepaalFinal(const string& staat);

public:
    NFA(const string& s): DFA(s) {type = "NFA";};
    DFA toDFA();
};


#endif //TA1_13_02_NFA_H
