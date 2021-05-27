 #include "DFA.h"
 using namespace std;

std::string productState(std::string state1, std::string state2) {
    return "(" + state1 + "," + state2 + ")";
}

std::map<std::string, State*> productEvaluation(State* currState, std::map<std::string, State*> baseStates,std::map<std::string, State*> newStates, std::vector<char> theAlphabet) {
    newStates[currState->getName()] = currState;

    for (auto c:theAlphabet) {
        State* theNextState = baseStates[currState->nextStates(c)[0]];
        if (newStates.find(theNextState->getName()) == newStates.end()) newStates = productEvaluation(theNextState, baseStates,newStates,theAlphabet);
    }

    return newStates;
}

bool DFA::accepts(const std::string &theString) {
    State *currentState = getStartState();

    if (theString.empty()) {
        if (currentState->isAccepting()) {
            return true;
        } else return false;
    }

    for (auto c:theString) {
    currentState = getState(currentState->nextStates(c)[0]);
        if (currentState == nullptr) {
            std::cerr << "No starting state" << std::endl;
            return false;
        }
    }

    if (currentState->isAccepting()) return true;
    return false;
}

DFA::DFA(DFA dfa1,DFA dfa2, bool intersection) : Automaton("") {
    setType("DFA");
    std::vector<char> theAlphabet = dfa1.getAlphabet();
    setAlphabet(theAlphabet);

    std::map<std::string, State*> DFA1States = dfa1.getStates();
    std::map<std::string, State*> DFA2States = dfa2.getStates();

    std::map<std::string, State*> baseStates;

    for (auto const &x:DFA1States) {
        State* dfa1State = x.second;
        for (auto const &y:DFA2States) {
            State* dfa2State = y.second;
            auto newState = new State(productState(dfa1State->getName(),dfa2State->getName()));

            if (dfa1State->isStarting() and dfa2State->isStarting()) {
                newState->setStarting(true);
                setStartState(newState);
            }

            if (intersection) {
                if (dfa1State->isAccepting() and dfa2State->isAccepting()) newState->setAccepting(true);
            } else {
                if (dfa1State->isAccepting() or dfa2State->isAccepting()) newState->setAccepting(true);
            }

            for (auto c:theAlphabet) {
                std::string s1 = dfa1State->nextStates(c)[0];
                std::string s2 = dfa2State->nextStates(c)[0];

                newState->setTransition(c, productState(s1,s2));
            }
            baseStates[newState->getName()] = newState;
        }
    }

    setStates(productEvaluation(getStartState(),baseStates,{},theAlphabet));
}

bool compareFunction (std::string a, std::string b) {return a<b;}

std::vector<std::string> getAcceptingStates(std::map<std::string,State*> theStates) {
    std::vector<std::string> v;
    for (auto x:theStates) {
        if (x.second->isAccepting()) v.push_back(x.first);
    }

    return v;
}

std::pair<int,int> getLocation(std::string state1, std::string state2, std::vector<std::vector<std::string>> TFATable) {
    std::pair<int,int> location;
    location.first = -1;
    location.second = -1;
    std::pair<int,int> otherLocation;
    for (int r = 0; r < (int) TFATable.size() - 1; r++) {
            if (TFATable[r][0] == state1) location.first = r;
            if (TFATable[r][0] == state2) otherLocation.first = r;
    }

    for (int k = 1; k < (int) TFATable[TFATable.size()-1].size();k++) {
            if (TFATable[TFATable.size()-1][k] == state2) location.second = k;
            if (TFATable[TFATable.size()-1][k] == state1) otherLocation.second = k;
    }
    if ((int) TFATable[location.first].size() > location.second and location.first > 0 and location.second > 0) return location;

    return otherLocation;
}

std::vector<std::vector<std::string>> combineNonDistinguishable(std::vector<std::vector<std::string>> nonDistinguishableStates, std::vector<std::vector<std::string>> combinedNonDis) {

    std::vector<std::string> currVector = nonDistinguishableStates[0];
    nonDistinguishableStates.erase(nonDistinguishableStates.begin());

    bool somethingChanged = true;

    while (somethingChanged) {
        somethingChanged = false;
        std::vector<std::vector<std::string>> v;
        for (auto x:nonDistinguishableStates) {
            bool found = false;
            for (auto item:x) {
                if (std::find(currVector.begin(),currVector.end(), item) != currVector.end()) {
                    currVector.insert(currVector.end(),x.begin(),x.end());
                    found = true;
                    somethingChanged = true;
                    continue;
                }
            }
            if (!found) v.push_back(x);
        }

        nonDistinguishableStates = v;
    }

return combinedNonDis;
}

std::map<std::string,State*> getCombinedTransitions(std::map<std::string,State*> baseStates, std::vector<std::string> newStates, std::vector<char> theAlphabet) {
    std::map<std::string,State*> allStates;
    for (auto stateName:newStates) {
        auto newState = new State(stateName);
        allStates[stateName] = newState;

        for (auto c:theAlphabet) {
            std::vector<std::string> v;
            for (auto state:getSeperateStates(stateName)) {
                v.push_back(baseStates[state]->nextStates(c)[0]);
                if (baseStates[state]->isAccepting()) newState->setAccepting(true);
                if (baseStates[state]->isStarting()) {
                    newState->setStarting(true);
                }
            }
            std::sort(v.begin(),v.end());
            newState->addTransition(c, getNewStateName(v));
        }
    }

    for (auto x:allStates) {
        for (auto c:theAlphabet) {
            for (auto string:newStates) {
                std::vector<std::string> v = getSeperateStates(x.second->nextStates(c)[0]);

                for (auto aNewState:newStates) {
                    for (auto p:getSeperateStates(aNewState)) {
                        if (std::find(v.begin(),v.end(), p) != v.end()) {
                            x.second->setTransition(c,aNewState);
                            break;
                        }
                    }
                }
            }
        }
    }

    for (auto x:baseStates) {
        bool breakOut = false;
        for (auto string:newStates) {
            for (auto cha:getSeperateStates(string)) {
                if (cha == x.first) breakOut = true;
            }
        }
        if (breakOut) continue;
        State* theState = x.second;
        std::string theOldName = theState->getName();
        theState->setName(getNewStateName({theOldName}));
        allStates[theState->getName()] = theState;
        for (auto c:theAlphabet) {
            std::string nextState = theState->nextStates(c)[0];
            theState->setTransition(c, nextState);

            for (auto string:newStates) {
                std::vector<std::string> v = theState->nextStates(c);

                for (auto aNewState:newStates) {
                    for (auto p:getSeperateStates(aNewState)) {
                        if (std::find(v.begin(),v.end(), p) != v.end()) {
                            theState->setTransition(c,aNewState);
                            break;
                        }
                    }
                }
            }
        }
    }

    for (auto x:allStates) {
        for (auto c:theAlphabet) {
            std::string theTransition = getNewStateName(x.second->nextStates(c));
            if (theTransition.at(1) != '{') x.second->setTransition(c,theTransition);
        }
    }


    return allStates;
}

DFA DFA::minimize() {
    DFA newDFA("");
    newDFA.setAlphabet(getAlphabet());

    std::vector<std::string> states;
    for (const auto& x:getStates()) {
        states.push_back(x.first);
    }

    //https://stackoverflow.com/questions/34757448/sorting-a-vector-of-objects-alphabetically-in-c
    std::sort(states.begin(),states.end(),compareFunction);

    std::vector<std::vector<std::string>> table;

    for (int r = 0; r < (int) states.size(); r++) {
        std::vector<std::string> v;
        table.push_back(v);

        if (r == (int) states.size() - 1) {
            for (int k = 0; k < (int) states.size(); k++) {
                if (k == 0) table[r].push_back(" ");
                else table[r].push_back(states[k-1]);
            }
        } else {
            for (int k = 0; k < r+2; k++) {
                if (k == 0) table[r].push_back(states[r+1]);
                else table[r].push_back("-");
            }
        }
    }

    std::vector<std::string> acceptingStates = getAcceptingStates(getStates());

    for (int r = 0; r < (int) states.size() - 1; r++) {
        for (int k = 1; k < (int) table[r].size(); k++) {
            std::string firstState = table[r][0];
            std::string secondState = table[table.size()-1][k];

            if (getState(firstState)->isAccepting() != getState(secondState)->isAccepting()) {
                table[r][k] = "X";
            }

        }
    }

    bool somethingChanged = true;
    while (somethingChanged){
        somethingChanged = false;
        for (int r = 0; r < (int) table.size() - 1; r++) {
            for (int k = 1; k < (int) table[r].size(); k++) {
                if (table[r][k] == "-") {
                    for (auto c:getAlphabet()) {
                        State* state1 = getState(table[r][0]);
                        State* state2 = getState(table[table.size()-1][k]);
                        std::string nextState1 = state1->nextStates(c)[0];
                        std::string nextState2 = state2->nextStates(c)[0];
                        if(nextState1 == nextState2) continue;
                        std::pair<int,int> location = getLocation(nextState1,nextState2, table);
                        if (table[location.first][location.second] == "X") {
                            table[r][k] = "X";
                            somethingChanged = true;
                        }
                    }
                }
            }
        }
    }

    std::vector<std::string> checkedStates;
    std::vector<std::string> theNewStates;

        for (int k = 1; k < (int) table[table.size()-1].size(); k++) {
            std::vector<std::string> v;
            bool newStateFound = false;
            for (int r = (int) table.size() - 2; r >= k - 1; r--) {
                if (table[r][k] == "-") {
                    std::string state1 = table[r][0];
                    std::string state2 = table[table.size() - 1][k];
                    if (find(checkedStates.begin(), checkedStates.end(), state1) == checkedStates.end()) {
                        v.push_back(state1);
                        checkedStates.push_back(state1);
                        newStateFound = true;
                    }
                    if (find(checkedStates.begin(), checkedStates.end(), state2) == checkedStates.end()) {
                        v.push_back(state2);
                        checkedStates.push_back(state2);
                        newStateFound = true;
                    }
                }
            }
            if (newStateFound) {
                std::sort(v.begin(),v.end());
                theNewStates.push_back(getNewStateName(v));
            }
        }

    std::map<std::string,State*> theOldStates = getStates();
    std::map<std::string,State*> theNewStateMap = getStates();

    for (auto x:theOldStates) {
        auto newStateForTheMap = new State(x.first);
        newStateForTheMap->setTransitions(x.second->getTransitions());
        newStateForTheMap->setStarting(x.second->isStarting());
        newStateForTheMap->setAccepting(x.second->isAccepting());

        theNewStateMap[newStateForTheMap->getName()] = newStateForTheMap;
    }

    newDFA.setStates(getCombinedTransitions(theNewStateMap,theNewStates,getAlphabet()));

    theNewStateMap = newDFA.getStates();

    for (auto x:theNewStateMap) {
        if (x.second->isStarting()) newDFA.setStartState(x.second);
    }

    TFATable = table;


    return newDFA;
}

void DFA::printTable() {
    for (auto & r : TFATable) {
        for (auto & k : r) {
            std::cout << k << "\t";
        }
        std::cout << std::endl;
    }

}



bool isEquivalent(std::pair<std::string,std::string> thePair, std::map<std::string,State*> dfa1States, std::map<std::string,State*> dfa2States,std::vector<char> theAlphabet, std::vector<std::pair<std::string,std::string>> *checkedPairs) {
    if (find(checkedPairs->begin(),checkedPairs->end(),thePair) != checkedPairs->end()) return true;
    if (dfa1States[thePair.first] == nullptr) {
        std::cout << thePair.first << std::endl;
        return false;
    }
    if (dfa2States[thePair.second] == nullptr) {
        std::cout << thePair.second << std::endl;
        return false;
    }
    if (dfa1States[thePair.first]->isAccepting() != dfa2States[thePair.second]->isAccepting()) return false;
    checkedPairs->push_back(thePair);

    for (auto c:theAlphabet) {
        std::pair<std::string,std::string> newPair;
        newPair.first = dfa1States[thePair.first]->nextStates(c)[0];
        newPair.second = dfa2States[thePair.second]->nextStates(c)[0];

        if (!isEquivalent(newPair,dfa1States,dfa2States,theAlphabet,checkedPairs)) return false;
    }
    checkedPairs->push_back(thePair);
    return true;
}
bool DFA::operator==(DFA dfa2) {
    std::pair<std::string,std::string> startPair = std::make_pair(getStartState()->getName(),dfa2.getStartState()->getName());
    auto theCheckedPairs = new std::vector<std::pair<std::string,std::string>>;
    return isEquivalent(startPair,getStates(),dfa2.getStates(),getAlphabet(),theCheckedPairs);
}


 vector<string> DFA::findWords(const std::string &theString){
     std::vector<char> alphabet = getAlphabet();
     State* state = pad(theString);
     vector<string> words;
     bool flag = false;

     for(auto a : alphabet){
         if(getState(state->nextStates(a)[0])->isAccepting()){
             words.push_back(theString+a);
             flag = true;
         }
     }
     if(flag){
         return words;
     }
     for(auto a : alphabet){
         if(!getState(state->nextStates(a)[0])->isDead()){
             vector<string> newWords = findWords(theString + a);
             words.insert(words.end(),newWords.begin(), newWords.end());
         }
     }
     return words;
 }

 vector<string> DFA::autocorrect1(std::string theString) {
     DFA curDFA = minimize();

     std::vector<char> alphabet = getAlphabet();
     bool flag = true;
     bool stop = false;
     vector<string> correctedWords;
     while(!theString.empty() or flag) {
         flag = false;
         if (curDFA.accepts(theString)) {
             correctedWords.push_back(theString);
             return correctedWords;
         }
         else{
             theString = theString.substr(0,theString.length() - 1);
             if (curDFA.accepts(theString)) {
                 correctedWords.push_back(theString);
                 stop = true;
                 //return correctedWords;
             }
             if(!curDFA.pad(theString)->isDead()){
                 vector<string> words = curDFA.findWords(theString);

                 correctedWords.insert(correctedWords.end(),words.begin() ,words.end());
                 return correctedWords;
             }
             if(stop) return correctedWords;
         }
     }

     return {""};
 }

State* DFA::pad(const std::string &theString) {
    State *currentState = getStartState();

    if (theString.empty()) {
        return currentState;
    }

    for (auto c:theString) {
        currentState = getState(currentState->nextStates(c)[0]);
        if (currentState == nullptr) {
            std::cerr << "No starting state" << std::endl;
        }
    }

    return currentState;
}
