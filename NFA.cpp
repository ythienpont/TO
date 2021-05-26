#include "NFA.h"
using namespace std;

void NFAState::addTransition(const char c, const std::string &state) {
    if (transitions.find(c) != transitions.end()) {
        transitions[c] = {state};
    } else {
        transitions[c].push_back(state);
    }
}

void NFAState::addTransition(const char c, const std::vector<std::string> &states) {
    if (transitions.find(c) != transitions.end()) {
        transitions[c] = states;
    } else {
        transitions[c].insert(transitions[c].end(),states.begin(),states.end());
    }
}

DFA NFA::toDFA() {

    DFA newDFA("");

    newDFA.setType("DFA");

    std::vector<char> theAlphabet = getAlphabet();
    newDFA.setAlphabet(theAlphabet);

    std::map<std::string, State*> oldNFAStates = getStates();
    std::map<std::string, State*> oldDFAStates;

    for (auto const& it:oldNFAStates) {
        State* newState = new State(it.first);
        State* oldState = it.second;

        newState->setName(oldState->getName());

        newState -> setAccepting(oldState->isAccepting());

        newState -> setStarting(oldState->isStarting());
        if (newState->isStarting()) {
            newDFA.setStartState(newState);
        }

        newState->setTransitions(oldState->getTransitions());

        oldDFAStates[newState->getName()] = newState;
    }

    State* newDFAStartState = new State(getNewStateName({newDFA.getStartState()->getName()}));
    newDFAStartState->setTransitions(newDFA.getStartState()->getTransitions());
    newDFAStartState->setStarting(true);
    newDFAStartState->setAccepting(newDFA.getStartState()->isAccepting());
    newDFA.setStartState(newDFAStartState);

    newDFA.setStates(lazyEvaluation(newDFA.getStartState(),oldDFAStates,{},theAlphabet,false));
    
    return newDFA;
}

bool NFA::accepts(const string&theString){
    DFA sscDFA = this->toDFA();

    return sscDFA.accepts(theString);

}
