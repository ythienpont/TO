#ifndef AUTOMATON_H
#define AUTOMATON_H
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <map>
#include <algorithm> // For std::sort and std::unique

#include "json.hpp"
using json = nlohmann::json;


class State {
    bool starting;
    bool accepting;
    std::string name;

    std::map<char, std::vector<std::string>> transitions;

public:
    explicit State(const std::string &theName);

    void setStarting(const bool starts) {starting = starts;}
    void setAccepting(const bool accepts) {accepting = accepts;}

    bool isStarting() {return starting;}
    bool isAccepting() {return accepting;}

    std::string getName() {return name;}
    void setName(const std::string &theName) {name = theName;}

    // Initieel werken we met een enkele staat, bij een NFA verandert dit
    // Transities worden voorgesteld als maps met een key en een (vector van) state(s)
    virtual void addTransition(const char c, const std::string &state);
    void setTransition(const char c, const std::string &state) {transitions[c] = {state};}

    std::map<char, std::vector<std::string>> getTransitions() {return transitions;}
    void setTransitions(const std::map<char, std::vector<std::string>> theTransitions) {transitions = theTransitions;}

    // Return the next states at given input
    std::vector<std::string> nextStates(const char input);

    bool isDead() const;
};

class Automaton {
    std::string type; // Stores if automaton is a DFA, NFA or eNFA

    std::map<std::string, State*> states;
    State* startState;

    std::vector<char> alphabet;

    char eps; // Char to represent epsilon, only used with eNFA
public:
    explicit Automaton(const std::string &fin);

    void setType(const std::string &theType) {type = theType;}
    std::string getType() {return type;}

    void setStates(const std::map<std::string, State*> theStates) {states = theStates;}
    std::map<std::string, State*> getStates() {return states;}

    void setState(const std::string &name, State* state) {states[name] = state;}
    State* getState(const std::string &name);

    void setAlphabet(const std::vector<char> &theAlphabet) {alphabet = theAlphabet;}
    std::vector<char> getAlphabet() {return alphabet;}

    void setStartState(State* theStartState) {startState = theStartState;}
    State* getStartState() {return startState;}

    void setEpsilon(const char epsChar) {eps = epsChar;}
    char getEpsilon() {return eps;}

    virtual bool accepts(const std::string &theString) = 0;
    json createJson();
    void print();
    void exportJson(const std::string& outputname); // voert de automaat uit naar een .json bestand
};

std::map<std::string, State*> lazyEvaluation(State* forEval,std::map<std::string, State*> baseStates, std::map<std::string, State*> newStates, std::vector<char> theAlphabet, bool intersection);

std::string getNewStateName(std::vector<std::string> transitions);

std::vector<std::string> getSeperateStates(const std::string &theState);

std::vector<std::string> getUniqueStates(std::vector<std::string> states);

std::map<char,std::vector<std::string>> combineStates(std::map<std::string, State*> baseStates,std::vector<char> theAlphabet);

bool combinedIsAccepting(std::map<std::string, State*> baseStates, bool intersection);

#endif //AUTOMATON_H
