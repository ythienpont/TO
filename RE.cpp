//
// Created by benjamin on 25-05-21.
//
#include "RE.h"
#include <string>
#include <ctype.h>
using namespace std;

RE::RE(string reg, char eps){
    regex = reg;
    epsilon = eps;
}
ENFA RE::toENFA() {
    ENFA newENFA("");
    vector<char>alphabet;
    newENFA.setType("ENFA");
    for(auto reg:regex){
        if(isalpha(reg) && reg != epsilon){
            alphabet.push_back(reg);
        }
    }
    newENFA.setAlphabet(alphabet);
    return newENFA;
}