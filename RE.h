//
// Created by benjamin on 25-05-21.
//
#ifndef RE_H
#define RE_H
#include <string>
#include "ENFA.h"

class RE{
public:
    std::string regex;
    char epsilon;
    int states;
    RE(const std::string &reg, const char eps);
    ~RE();
    ENFA toENFA();
    DFA toDFA();
    ENFA ster(ENFA enfa);
    ENFA concatenatie(ENFA enfa1, ENFA enfa2);
    ENFA plus(std::vector<ENFA> enfa);
};
#endif //RE_H
