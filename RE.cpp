//
// Created by benjamin on 25-05-21.
//
#include "RE.h"
#include <string>
#include <stack>
using namespace std;

RE::RE(string reg, char eps){
    regex = reg;
    epsilon = eps;
    states = 0;
}
ENFA RE::toENFA() {
    //inspiratie gehaald uit https://github.com/nitishabharathi/RE---NFA---DFA-Simulator/blob/master/RE_NFA.cpp
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
        if(reg == '('){
            operatoren.push(reg);
        }else if(reg == ')'){

        }else if(reg == '+'){
            operatoren.push(reg);
        }else if(reg == '*'){
            operatoren.push(reg);
        }else if(reg == '.'){
            operatoren.push(reg);
        }else{
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
    ++states;
    vector<string>eps_transitions;
    State* state = new State(s);
    state->setStarting(true);
    state->setAccepting(false);
    eps_transitions.push_back(enfa.getStartState()->getName());
    enfa.getStartState()->setStarting(false);
    string z(1,states);
    ++states;
    State* state2 = new State(z);
    enfa1.setState(z,state2);
    eps_transitions.push_back(z);
    state->addTransitions(epsilon, eps_transitions);
    for(auto it:enfa.getStates()){
        if(it.second->isAccepting()){
            it.second->setAccepting(false);
            it.second->addTransition(epsilon, z);
        }
    }
    enfa1.setState(enfa.getStartState()->getName(), enfa.getStartState());
    enfa1.setStartState(state);
}