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
    RE(string reg, char eps);
    ENFA toENFA();
};
#endif //RE_H
