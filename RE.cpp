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
    newENFA.setEpsilon(epsilon);
    vector<string> currentState;
    int states = 0;
    int haken;
    if(regex.at(0) == '(' && regex.at(regex.size() - 1) == ')'){
        regex.erase(regex.begin());
        regex.erase(regex.end());
    }
    for(auto reg:regex){

        if(isalpha(reg) && reg != epsilon){
            alphabet.push_back(reg);
            ENFA enfa("");
            vector<char> alp = {reg};
            enfa.setAlphabet(alp);
            enfa.setEpsilon(epsilon);
            string s(1,states);
           State* state = new State(s);
           state->setStarting(true);
           state->setAccepting(false);
           enfa.setStartState(state);
           ++states;
           string z(1, states);
           State* state2 = new State(z);
           state2->setStarting(false);
           state2->setAccepting(true);
           enfa.setState(z,state2);
        }else if(reg == '('){
            ++haken;
            if(regex.find(regex.find(')',reg)+1) == '*'){

            }
        }else if(reg == ')'){
            --haken;

        }else if(reg == '+'){
            if(haken == 0){

            }else{

            }
        }else if(reg == epsilon){

        }else if(reg == '*'){

        }else if(reg == '.'){
            if(regex.find(regex.find('*',reg)-1) == ')'){

            }
        }
    }
    newENFA.setAlphabet(alphabet);
    return newENFA;
}

ENFA RE::plus(ENFA enfa1, ENFA enfa2) {

}

ENFA RE::concatenatie(ENFA enfa1, ENFA enfa2) {

}
ENFA RE::ster(ENFA enfa) {

}