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
    string s(1, states);
    ++states;
    string z(1,states);
    ++states;
    State* state = new State(s);
    State* state2 = new State(z);
    enfa.setType("ENFA");
    enfa.setEpsilon(epsilon);
    vector<char> alphabet;
    alphabet = enfa1.getAlphabet();
    for(auto it: enfa2.getAlphabet()){
        if(count(alphabet.begin(), alphabet.end(), it) == 0){
            alphabet.push_back(it);
        }
    }
    vector<string> transition;
    transition.push_back(enfa1.getStartState()->getName());
    enfa1.getStartState()->setStarting(false);
    transition.push_back(enfa2.getStartState()->getName());
    enfa2.getStartState()->setStarting(false);
    state->addTransitions(epsilon, transition);
    for(auto it:enfa1.getStates()){
        if(it.second->isAccepting()){
            it.second->addTransition(epsilon,z);
            it.second->setAccepting(false);
        }
        enfa.setState(it.second->getName(),it.second);
    }
    for(auto it:enfa2.getStates()){
        if(it.second->isAccepting()){
            it.second->addTransition(epsilon,z);
            it.second->setAccepting(false);
        }
        enfa.setState(it.second->getName(),it.second);
    }
    delete state;
    delete state2;
    return enfa;
}

ENFA RE::concatenatie(ENFA enfa1, ENFA enfa2) {
    ENFA enfa("");
    enfa = enfa1;
    for(auto& it:enfa.getStates()){
        if(it.second->isAccepting()){
            it.second->setAccepting(false);
            it.second->addTransition(epsilon,enfa2.getStartState()->getName());
        }
    }
    enfa2.getStartState()->setAccepting(false);
    for(auto it: enfa2.getStates()){
        enfa.setState(it.second->getName(),it.second);
    }
    return enfa;
}
ENFA RE::ster(ENFA enfa) {
    ENFA enfa1("");
    enfa1 = enfa;
    string s(1,states);
    ++states;
    vector<string>eps_transitions;
    State* state = new State(s);
    state->setStarting(true);
    state->setAccepting(false);
    eps_transitions.push_back(enfa.getStartState()->getName());
    enfa1.getStartState()->setStarting(false);
    string z(1,states);
    ++states;
    State* state2 = new State(z);
    eps_transitions.push_back(z);
    state->addTransitions(epsilon, eps_transitions);
    for(auto& it:enfa1.getStates()){
        if(it.second->isAccepting()){
            it.second->setAccepting(false);
            it.second->addTransition(epsilon, z);
        }
    }
    enfa1.setState(enfa.getStartState()->getName(), enfa.getStartState());
    enfa1.setStartState(state);
    enfa1.setState(s,state);
    state2->setAccepting(true);
    enfa1.setState(z,state2);
    delete state;
    delete state2;
    return enfa1;
}