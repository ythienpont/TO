#include "ENFA.h"
#include <vector>
#include <set>
/*int size1 = 1;
     int size2 = -1;
     while(size1 != size2){
         size1 = closure.size();



         size2 = closure.size();
     }
     while(!cur->nextStates(epsChar).empty()){

     }*/
/*NFA ENFA::toNFA(){
    std::map<std::string,State*> theStates = getStates();
    std::vector<char> theAlphabet = getAlphabet();
    char epsChar = getEpsilon();
    NFA newNFA("");
    newNFA.setAlphabet(theAlphabet);
    newNFA.setType("NFA");

    for (auto x:theStates) {
        State* theState = x.second;

        std::set<std::string> closure;
        std::vector<std::string> epsilonStates = theState->nextStates(epsChar);

        for(auto e : epsilonStates){
            closure.insert(e);
        }

        for(const auto& c : closure){
            State* cur = getState(c);
            for(const auto& d : cur->nextStates(epsChar)){
                closure.insert(d);
            }
        }
    }

    return newNFA;
}*/

NFA ENFA::toNFA() {
    std::map<std::string,State*> theStates = getStates();
    std::vector<char> theAlphabet = getAlphabet();

    char epsChar = getEpsilon();

    NFA newNFA("");

    newNFA.setAlphabet(theAlphabet);
    newNFA.setType("NFA");

    std::map<std::string, std::vector<std::string>> closureMap; // de closures van alle staten
    //closures initialiseren
    for(auto s : theStates) {
        State* state = s.second;
        std::vector<std::string> closure = {s.first}; // = closure
        std::vector<std::string> epsilonStates = state->nextStates(epsChar);

        while (!epsilonStates.empty()) {
            closure.insert(closure.end(), epsilonStates.begin(), epsilonStates.end());

            std::vector<std::string> v1;
            for (const auto& state1:epsilonStates) {
                State *epsilonState = getState(state1);
                std::vector<std::string> v2 = epsilonState->nextStates(epsChar);
                for (auto item:v2) {
                    if (find(closure.begin(), closure.end(), item) == closure.end())
                        v1.push_back(item);
                }
            }
            epsilonStates = v1;
        }
        closure = getUniqueStates(closure);
        closureMap[s.first] = closure;
    }
    // einde closures initialiseren

    /*for(auto e : closureMap){
        std::cout << e.first << ": ";
        for(auto z : e.second) {
            std::cout << z << " ";
        }
        std::cout << std::endl;

    }
    std::cout << std::endl;*/


    for (auto x:theStates) {
        State* theState = x.second;
        State* newState = new State(theState->getName());
        //newState->setAccepting(theState->isAccepting());
        newState->setStarting(theState->isStarting());

        if (newState->isStarting()) setStartState(newState);

        std::map<char,std::vector<std::string>> theTransitions;

        // Epsilon
        /*std::vector<std::string> currentStates; // = closure
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

        std::cout <<"staat: "<<theState->getName() << " : ";
        */

        std::vector<std::string> currentStates = closureMap[x.first]; // = closures van de huidige staat
        newState->setAccepting(false);
        for(auto z : currentStates){
           if(getState(z)->isAccepting()){
               newState->setAccepting(true);
           }
           //std::cout << getState(z)->getName() << " ";
       }
        //std::cout << std::endl;


        for (auto c:theAlphabet) {
            // Input

            //in dit deeltje voeg ik de volgende states van een closure staat toe aan trans
            std::vector<std::string> trans;
            for (const auto& state:currentStates) {
                std::vector<std::string> v2 = getState(state)->nextStates(c);
                trans.insert(trans.end(),v2.begin(),v2.end());
            }

            /*std::vector<std::string> trans;
            for (const auto& state: v9) {
                if(theState->getName() == "2" and c == 'k') {


                    //std::cout << theState->getName() << " " << c << " " << state << std::endl;
                }
                //std::vector<std::string> staten = getState(state)->nextStates(c);
                trans.push_back(state);

                //if(!staten.empty()){
                    //trans.insert(trans.end(),staten.begin(), staten.end() );
                    //std::cout << theState->getName() << " "<< c << " " << staten[0] << std::endl;
                //}
            }*/

            // de eigen next states toevoegen aan trans
            for(const auto& r : theState->nextStates(c)){
                trans.push_back(r);
                //std::cout << theState->getName() << " " << r<<std::endl;
            }

            //std::cout << theState->getName() << " "<< c << " :  ";
            for(auto t: trans){ // CL(0)=5 CL(1) = 6, trans = {0,1}, hierna; trans = {0,1,5,6}
                //std::cout << t << " ";
                trans.insert(trans.end(), closureMap[t].begin(), closureMap[t].end());
            }
            //std::cout << std::endl;


            trans = getUniqueStates(trans);
            theTransitions[c] = trans;
        }
        newState->setTransitions(theTransitions);
        newNFA.setState(newState->getName(),newState);
    }
    return newNFA;
}

/*
NFA ENFA::toNFA() {
    std::map<std::string,State*> theStates = getStates();
    std::vector<char> theAlphabet = getAlphabet();

    char epsChar = getEpsilon();

    NFA newNFA("");

    newNFA.setAlphabet(theAlphabet);
    newNFA.setType("NFA");

    State* deadState = new State("DEAD");
    newNFA.setState("DEAD", deadState);

    for (auto c:theAlphabet) {
        deadState->setTransition(c, "DEAD");
    }

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

            if (currentStates.empty()) {
                currentStates = {"DEAD"};
            }

            theTransitions[c] = currentStates;
        }

        newState->setTransitions(theTransitions);
        newNFA.setState(newState->getName(),newState);
    }

    return newNFA;
}*/
DFA ENFA::toDFA() {
    return toNFA().toDFA();
}
ENFA::~ENFA(){

}
