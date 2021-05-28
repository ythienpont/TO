//
// Created by benjamin on 25-05-21.
//
#include "RE.h"
#include <string>
using namespace std;

RE::RE(const std::string &reg, const char eps){
    regex = reg;
    epsilon = eps;
    states = 0;
}
ENFA RE::toENFA() {
    //inspiratie gehaald uit https://github.com/nitishabharathi/RE---NFA---DFA-Simulator/blob/master/RE_NFA.cpp
    ENFA newENFA("");
    vector<char> operatoren;
    vector<ENFA> automaat;
    vector<char>alphabet;
    newENFA.setType("ENFA");
    newENFA.setEpsilon(epsilon);
    if(regex.at(0) == '(' && regex.at(regex.size() - 1) == ')'){
        regex.erase(regex.begin());
        regex.erase(regex.end());
    }
    for(auto reg = 0; reg != regex.size(); reg++){
        if(regex[reg] != '(' && regex[reg] != ')' && regex[reg] != '+' && regex[reg] != '.' && regex[reg] != '*'){
            ENFA enfa("");
            enfa.setType("ENFA");
            if(regex[reg] != epsilon){
                vector<char> alp = {regex[reg]};
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
            ++states;
            State* state2 = new State(z);
            state->addTransition(regex[reg],z);
            state2->setStarting(false);
            state2->setAccepting(true);
            enfa.setState(z,state2);
            automaat.push_back(enfa);

        }else if(regex[reg] == '(') {
            operatoren.push_back(regex[reg]);
        }else if(regex[reg] == '+'){
            operatoren.push_back(regex[reg]);
        }else if(regex[reg] == '*'){
            operatoren.push_back(regex[reg]);
        }else if(regex[reg] == '.'){
            operatoren.push_back(regex[reg]);
        }else{
            if(reg != regex.size() -1 && isalpha(regex.at(reg+1))){
                operatoren.push_back(regex[reg]);
                operatoren.push_back('.');
            }else{
                operatoren.push_back(regex[reg]);
            }

        }
    }
    while(automaat.size() != 1){
        int autom = 0;
        vector<ENFA> aut = automaat;
        automaat = {};
        vector<char>symb = operatoren;
        operatoren = {};
        vector<ENFA> ENFA;
        for(auto it = 0; it != symb.size(); it++){
            while(autom <= aut.size()){
                if(symb[it] == '+'){
                    if(symb[it] == '('){
                        operatoren.push_back('+');
                    }else{
                        if(ENFA.size() == 0){
                            ENFA.push_back(aut[autom]);
                            ++autom;
                        }
                        ENFA.push_back(aut[autom]);
                        ++autom;
                    }
                }else if( symb[it] == ')'){
                    if(ENFA.size() > 0){
                        automaat.push_back(plus(ENFA));
                        ENFA = {};
                    }
                }else if(symb[it] == '*'){
                    if(symb[it-1] == ')'){
                        automaat.back() = ster(automaat.back());
                    }else{
                        automaat.push_back(ster(aut[autom]));
                        ++autom;
                    }
                }else if(symb[it] == '.'){
                    if(symb[it-1] == ')'){
                        automaat.back() = concatenatie(automaat.back(), aut[autom]);
                        ++autom;
                    }else{
                        ++autom;
                        automaat.push_back(concatenatie(aut[autom-1], aut[autom]));
                        ++autom;
                    }
                }else if(symb[it] == '('){
                    if(symb[it-1] != '(' && ENFA.size() > 0){
                        automaat.push_back(plus(ENFA));
                        ENFA = {};
                    }
                }
            }
            if(ENFA.size() > 0){
                automaat.push_back(plus(ENFA));
                ENFA = {};
            }

        }
    }
    newENFA = automaat[0];
    return newENFA;
}
RE::~RE(){

}
ENFA RE::plus(vector<ENFA> enfa1) {
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
    alphabet = enfa1.begin()->getAlphabet();
    for(auto it = 0; it != enfa1.size(); it++){
        for(auto& i:enfa1[it].getAlphabet()){
            if(count(alphabet.begin(), alphabet.end(), i) == 0){
                alphabet.push_back(i);
            }
        }
    }
    vector<string> transition;
    for(auto it = 0; it != enfa1.size(); it++){
        transition.push_back(enfa1[it].getStartState()->getName());
        enfa1[it].getStartState()->setStarting(false);
    }
    state->addTransitions(epsilon, transition);
    for(auto it = 0; it != enfa1.size(); it++){
        for(auto& i:enfa1[it].getStates()){
            if(i.second->isAccepting()){
                i.second->addTransition(epsilon,z);
                i.second->setAccepting(false);
            }
            enfa.setState(i.first,i.second);
        }
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
