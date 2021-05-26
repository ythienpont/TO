//
// Created by benjamin on 25-05-21.
//
#include "RE.h"
#include <string>
#include <ctype.h>
#include <stack>
using namespace std;

RE::RE(string reg, char eps){
    regex = reg;
    epsilon = eps;
    states = 0;
}
ENFA RE::toENFA() {
    ENFA newENFA("");
    stack<char> operatoren;
    stack<ENFA> automaat;
    vector<char>alphabet;
    newENFA.setType("ENFA");
    newENFA.setEpsilon(epsilon);
    vector<string> currentState;
    if(regex.at(0) == '(' && regex.at(regex.size() - 1) == ')'){
        regex.erase(regex.begin());
        regex.erase(regex.end());
    }
    for(auto reg:regex){
        if(isalpha(reg)){
            ENFA enfa("");
            enfa.setType("ENFA");
            if(reg != epsilon){
                vector<char> alp = {reg};
                enfa.setAlphabet(alp);
            }
            enfa.setEpsilon(epsilon);
            string s(1,states);
            State* state = new State(s);
            state->setStarting(true);
            state->setAccepting(false);
            enfa.setStartState(state);
            ++states;
            string z(1, states);
            State* state2 = new State(z);
            state->addTransition(reg,z);
            state2->setStarting(false);
            state2->setAccepting(true);
            enfa.setState(z,state2);
            automaat.push(enfa);
            delete state;
            delete state2;
        }else if(reg == '('){
            operatoren.push(reg);
        }else if(reg == ')'){

        }else if(reg == '+'){
            operatoren.push(reg);
        }else if(reg == '*'){
            operatoren.push(reg);
        }else if(reg == '.'){
            operatoren.push(reg);
        }
    }
    newENFA.setAlphabet(alphabet);
    return newENFA;
}

ENFA RE::plus(ENFA enfa1, ENFA enfa2) {
    ENFA enfa("");
}

ENFA RE::concatenatie(ENFA enfa1, ENFA enfa2) {
    ENFA enfa("");
}
ENFA RE::ster(ENFA enfa) {
    ENFA enfa1("");
    string s(1,states);
    State* state = new State(s);
    state->setStarting(true);
    state->setAccepting(false);
    enfa1.setStartState(state);



}