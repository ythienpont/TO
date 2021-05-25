#include "Automaton.h"

std::string getNewStateName(std::vector<std::string> transitions) {
    //https://stackoverflow.com/questions/16476099/remove-duplicate-entries-in-a-c-vector
    // Zo krijg je geen states als {1,1}
    std::sort(transitions.begin(), transitions.end()); 
    auto last = std::unique(transitions.begin(), transitions.end());
    transitions.erase(last, transitions.end());
    int transitionAmt = transitions.size();

    std::string newStateName = "{";

    for (int i=0; i < transitionAmt; i++) {
        newStateName += transitions[i];
        if (i != transitionAmt-1) newStateName += ",";
    }

    newStateName += '}';

    return newStateName;
}

std::vector<std::string> getSeperateStates(std::string theState) {
    std::vector<std::string> seperateStates;

    for (auto c:theState) {
        if (c != '{' and c != '}' and c != ',' and c != ' ' and c != '(' and c != ')') {
            std::string seperateState(1,c);
            seperateStates.push_back(seperateState);
        }
    }

    return seperateStates;
}

//https://www.geeksforgeeks.org/stdunique-in-cpp/
std::vector<std::string> getUniqueStates(std::vector<std::string> states) {
    std::vector<std::string>::iterator ip;
    std::sort(states.begin(),states.end());

    ip = std::unique(states.begin(), states.begin() + states.size());

    states.resize(std::distance(states.begin(),ip));

    return states;
}


std::map<char,std::vector<std::string>> combineStates(std::map<std::string, State*> baseStates,std::vector<char> theAlphabet) {
    std::map<char,std::vector<std::string>> newTransitions;

    for (auto c:theAlphabet) {
        std::vector<std::string> v1;
        for (auto x:baseStates) {
            std::vector<std::string> v2 = x.second->nextStates(c);
            v1.insert(v1.end(),v2.begin(),v2.end());
        }

        newTransitions[c] = getUniqueStates(v1);
    }

    return newTransitions;
}

bool combinedIsAccepting(std::map<std::string, State*> baseStates, bool intersection) {
    if (intersection) {
        for (auto x:baseStates){
            if (!x.second->isAccepting()) return false;
        }

        return true;
    }

    for (auto x:baseStates){
        if (x.second->isAccepting()) return true;
    }

    return false;
}

std::map<std::string, State*> lazyEvaluation(State* forEval,std::map<std::string, State*> baseStates, std::map<std::string, State*> newStates, std::vector<char> theAlphabet, bool intersection) {
    newStates[forEval->getName()] = forEval;

    for (auto c:theAlphabet) {
        std::string newStateName = getNewStateName(forEval->nextStates(c));

        if (newStates.find(newStateName) == newStates.end()) {
            State* newState = new State(newStateName);
            newState->setStarting(false);

            std::map<std::string, State*> individiualStates;

            std::vector<std::string> theNextStates = getUniqueStates(forEval->nextStates(c));
            for(auto state:theNextStates) {
                individiualStates[state] = baseStates[state];
            }

            newState->setTransitions(combineStates(individiualStates,theAlphabet));
            newState->setAccepting(combinedIsAccepting(individiualStates,intersection));
            newStates = lazyEvaluation(newState,baseStates,newStates,theAlphabet,intersection);
        }

        forEval->setTransition(c,newStateName);
    }

    return newStates;
}

//Hulpfunctie
 std::string multipleStates(std::vector<std::string> transitions) {
    int transitionAmt = transitions.size();

    if (transitionAmt == 1) return transitions[0];
    
    std::string newStateName = "{";
    
    for (int i=0; i < transitionAmt; i++) {
        newStateName += transitions[i];
        if (i != transitionAmt-1) newStateName += ", ";
    }

    newStateName += '}';

    return newStateName;
}

State::State(const std::string &theName) {
    name = theName;
    accepting = false;
    starting = false;
}

void State::addTransition(const char c, const std::string &state) {
    std::map<char, std::vector<std::string>>::const_iterator it = transitions.find(c);

    // If the entry already exists, append to vector
    if (it!=transitions.end()) {
        transitions[c].push_back(state);
        return;
    }

    std::vector<std::string> newEntry = {state};
    transitions[c] = newEntry;
}

// Return the next states at given input
std::vector<std::string> State::nextStates(const char input) {
    std::map<char, std::vector<std::string>>::const_iterator it = transitions.find(input);

    if (it!=transitions.end()) {
        return transitions[input];
    } 
    
    return {};
}

Automaton::Automaton(const std::string &fin) {
    if (fin == "") { // Soms willen we gewoon een lege automaat
        type="DFA";
        return;
    } 

    std::ifstream input(fin);
    json j;
    input >> j;

    setType(j["type"]);

    std::vector<char> theAlphabet;
    for (json::iterator it = j["alphabet"].begin(); it != j["alphabet"].end(); ++it) {
        std::string theString = it->get<std::string>();
        theAlphabet.push_back(theString.at(0));
    }

    setAlphabet(theAlphabet);

    if (getType() == "ENFA") setEpsilon(j["eps"].get<std::string>().at(0)); 

    setStartState(nullptr);

    std::map<std::string,State*> theStates;
    for (auto& state:j["states"]) {
        std::string name = state["name"];
        State* newState = new State(name);

        newState->setAccepting(state["accepting"]);
        newState->setStarting(state["starting"]);

        if(newState -> isStarting()) setStartState(newState);

        theStates.insert({name, newState});
    }

    setStates(theStates);

    for (auto& t:j["transitions"]) {
        std::string symbol = t["input"];
        char theInput = symbol.at(0);

        State* theState = getState(t["from"]);
        
        if (theState != nullptr) theState -> addTransition(theInput, t["to"]);
    }

}

State* Automaton::getState(const std::string &name) {
    std::map<std::string, State*>::const_iterator it = states.find(name);

    if (it!=states.end()) {
        return states[name];
    } 
    
    return nullptr;
}


void Automaton::print() {
    json j;
    j["type"] = type;
    j["alphabet"] = json::array();

    //Alphabet

    for (auto input:alphabet) {
        std::string s(1,input);
        j["alphabet"].push_back(s);
    }

    if (type == "ENFA") j["eps"] = eps;

    //States

    j["states"] = json::array();
    j["transitions"] = json::array();

    std::map<std::string, State*>::const_iterator it;

    for (it = states.begin(); it != states.end(); it++) {
        json state;
        state["name"] = it->first;

        if (it->second->isStarting()) state["starting"] = true;
        else state["starting"] = false;

        if (it->second->isAccepting()) state["accepting"] = true;
        else state["accepting"] = false;
        
        j["states"].push_back(state);

        //Transitions

        State* theState = it->second;

        if (type == "DFA") {
            for (auto input:alphabet) {
                json transition;
                transition["from"] = it->first;
                transition["to"] = theState->nextStates(input)[0];

                std::string s(1, input);
                transition["input"] = s;
                j["transitions"].push_back(transition);
            }
        } else {
            for (auto input:alphabet) {
                json transition;
                transition["from"] = it ->first;
                transition["to"] = multipleStates(theState->nextStates(input));

                std::string s(1, input);
                transition["input"] = s;
                j["transitions"].push_back(transition);

            }
        }     
    }
    std::cout << std::setw(4) << j << std::endl;
}
