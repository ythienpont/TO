//
// Created by benjamin on 25-05-21.
//

#ifndef RE_H
#define RE_H
#include <string>
#include "ENFA.h"
using namespace std;
class RE{
public:
    string regex;
    char epsilon;
    int states;
    RE(string reg, char eps);
    ENFA toENFA();
    ENFA ster(ENFA enfa);
    ENFA concatenatie(ENFA enfa1, ENFA enfa2);
    ENFA plus(ENFA enfa1, ENFA enfa2);
};
#endif //RE_H
