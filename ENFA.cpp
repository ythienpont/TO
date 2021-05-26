#include "ENFA.h"

NFA ENFA::toNFA() {
    std::map<std::string,State*> theStates = getStates();
    std::vector<char> theAlphabet = getAlphabet();
    
    char epsChar = getEpsilon();

    NFA newNFA("");

    newNFA.setAlphabet(theAlphabet);
    newNFA.setType("NFA");

    for (auto x:theStates) {
        State* theState = x.second;
        State* newState = new State(theState->getName());
        newState->setAccepting(theState->isAccepting());
        newState->setStarting(theState->isStarting());

        if (newState->isStarting()) setStartState(newState);

        std::map<char,std::vector<std::string>> theTransitions;

        for (auto c:theAlphabet) {
            // Epsilon
            std::vector<std::string> currentStates;
            std::vector<std::string> epsilonStates = theState->nextStates(epsChar);

            while (!epsilonStates.empty()) {
                currentStates.insert(currentStates.end(),epsilonStates.begin(),epsilonStates.end());

                std::vector<std::string> v1;
                for (auto state:epsilonStates) {
                    State* epsilonState = getState(state);
                    std::vector<std::string> v2 = epsilonState->nextStates(epsChar);
                    for (auto item:v2) {
                        if (find(currentStates.begin(),currentStates.end(),item) == currentStates.end()) v1.push_back(item);
                    }
                }
                epsilonStates = v1;
            }

            if (find(currentStates.begin(),currentStates.end(),theState->getName()) == currentStates.end()) currentStates.push_back(theState->getName());


            // Input
            std::vector<std::string> v1;
            for (auto state:currentStates) {
                std::vector<std::string> v2 = getState(state)->nextStates(c);
                v1.insert(v1.end(),v2.begin(),v2.end());
            }

            currentStates = v1;

            // Epsilon
            v1.clear();
            for (auto state:currentStates) {
                epsilonStates.clear();
                epsilonStates = getState(state)->nextStates(epsChar);
                while (!epsilonStates.empty()) {
                    v1.insert(v1.end(),epsilonStates.begin(),epsilonStates.end());

                    std::vector<std::string> v;
                    for (auto state:epsilonStates) {
                        State* epsilonState = getState(state);
                        std::vector<std::string> vx = epsilonState->nextStates(epsChar);
                        for (auto item:vx) {
                            if (find(v1.begin(),v1.end(),item) == v1.end()) v.push_back(item);
                        }
                    }
                    epsilonStates = v;
                }

            }

            currentStates.insert(currentStates.end(), v1.begin(), v1.end());

            currentStates = getUniqueStates(currentStates);

            theTransitions[c] = currentStates;
        }

        newState->setTransitions(theTransitions);
        newNFA.setState(newState->getName(),newState);
    }

    return newNFA;
}
DFA ENFA::toDFA() {
    return toNFA().toDFA();
}
ENFA::~ENFA(){

}
