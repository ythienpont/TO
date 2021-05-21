//
// Created by Alperen on 25/03/2021.
//

#include "NFA.h"
#include <vector>
#include <algorithm>
#include <set>
#include <string>

string benaam(string& str){
    sort(str.begin(),str.end()); // de string sorteren
    string staat = "{";

    for(const auto& c:str){
        staat = staat + c + ',';
    }

    staat = staat.substr(0,staat.size()-1);
    staat += "}";
    return staat;
}


bool NFA::bepaalFinal(const string& staat){
    for(auto c: staat){
        if(centralUnit[string(1,c)]->final){
            return true;
        }
    }
    return false;
}


void removeDuplicates(string& str)
{
    set<string> set;
    for(auto c: str){
        set.insert(string(1,c));
    }

    str.clear();
    for(const auto& s: set){
        str += s;
    }
}


DFA NFA::toDFA() { // lazy evaluation
    DFA dfa;
    dfa.alphabet =  alphabet;

    Node* startknoop = new Node();
    startknoop->naam = start->naam;
    dfa.centralUnit[start->naam] = startknoop;
    dfa.start = startknoop;

    Node* deadstate = new Node();
    deadstate->naam = "dead";
    deadstate->final = false;
    for (const auto &c : alphabet) { // dode staat transities
        deadstate->pointers[c] = {deadstate};
    }

    vector<string> tempVec;
    for (const auto &c : alphabet) { // start staat transities
        string unie;

        if (!start->pointers[c].empty()) {
            for (auto s : start->pointers[c]) {
                unie += s->naam;
            }
        }

        if (!unie.empty()) {
            removeDuplicates(unie);
            if(!dfa.centralUnit[unie]){
                Node* knoop = new Node();
                knoop->naam = unie;
                dfa.centralUnit[unie] = knoop;
                tempVec.push_back(unie);
            }
            dfa.start->pointers[c].push_back(dfa.centralUnit[unie]);
        }
        else{
            if(!dfa.centralUnit["dead"]){
                dfa.centralUnit["dead"] = deadstate;
            }
            dfa.start->pointers[c].push_back(deadstate);
        }
    }

    string temp;

    while(!tempVec.empty()) { // alle andere transities
        temp = tempVec[0];
        for (const auto &c : alphabet) {
            string unie;
            for (auto nfaStaat:temp) {
                if (!centralUnit[string(1,nfaStaat)]->pointers[c].empty()) {
                    for (auto s : centralUnit[string(1,nfaStaat)]->pointers[c]) {
                        unie += s->naam;
                    }
                }
            }

            if (!unie.empty()) {
                removeDuplicates(unie);
                if (!dfa.centralUnit[unie]) {
                    Node* knoop = new Node();
                    knoop->naam = unie;
                    dfa.centralUnit[unie] = knoop;
                    tempVec.push_back(unie);
                }
                dfa.centralUnit[temp]->pointers[c].push_back(dfa.centralUnit[unie]);
            }
            else{
                if(!dfa.centralUnit["dead"]){
                    dfa.centralUnit["dead"] = deadstate;
                }
                dfa.centralUnit[temp]->pointers[c].push_back(deadstate);
            }
        }
        tempVec.erase(tempVec.begin());
    }

    for(const auto& s: dfa.centralUnit){
        s.second->final = bepaalFinal(s.second->naam);
        s.second->naam = benaam(s.second->naam);
    }

    return dfa;
}




/*vector<string> combinaties(const vector<string>& str) {
    vector<string> set;
    string leeg;
    set.push_back(leeg);
    for(const auto& c: str){
        int size = set.size();
        for(int e=0; e< size ; e++){
            set.push_back(set[e]+c);
        }
    }
    set.erase(set.begin());
    return set;
}

vector<string> benaam(const vector<string>& str){
    vector<string> vec;
    for(const auto& s:str){
        string staat = "{";

        string temp = s;
        sort(temp.begin(),temp.end());

        for(const auto& c:temp){
            staat += c + ',';
        }
        staat = staat.substr(0,staat.size()-1);
        staat += "}";
        vec.push_back(staat);
    }
    return vec;
}
bool NFA::bepaalFinal(const string& staat){
    int a=1;
    for(auto c: staat){
        if(a%2==0){
            if(centralUnit[string(1,c)]->final){
                return true;
            };
        }
        a++;
    }

    return false;
}*/


/*
DFA NFA::toDFA() {
    DFA dfa;
    dfa.alphabet =  alphabet;

    vector<string> key;
    for(auto & i : centralUnit) {
        key.push_back(i.first);
    }
    vector<string> combs = combinaties(key);
    //vector<string> combs = benaam(combinaties(key));

    Node* dead = new Node();
    dead->naam = "dead";
    dead->final = false;
    for(const auto& a:alphabet){
        dead->pointers[a].push_back(dead);
    }
    dfa.centralUnit["dead"] = dead;

    for(const auto& i : combs){
        Node* knoop = new Node();
        knoop->naam = i;
        knoop->final = bepaalFinal(i);
        for(const auto& a1:alphabet){
            knoop->pointers[a1].push_back(dead); // elke transitie naar de dead state
        }
        dfa.centralUnit[i] = knoop;
    }
    //dfa.start = dfa.centralUnit['{' + start->naam + '}'];
    dfa.start = dfa.centralUnit[start->naam];


    for(const auto& f: combs){
        for(const auto& a2: alphabet){
            string to;
            //int a=1;
            for(auto c: f) {
                //if (a % 2 == 0) {
                    if (!centralUnit[string(1, c)]->pointers[a2].empty()) {
                        for (auto q: centralUnit[string(1, c)]->pointers[a2]) {
                            to += q->naam;
                        }

                    }
                //}
                //a++;

            }

            if(!to.empty()){
                removeDuplicates(to);
                sort(to.begin(), to.end());
                dfa.centralUnit[f]->pointers[a2].push_back(dfa.centralUnit[to]);
            }


        }
    }

    removeDeadStates(dfa);

    return dfa;
}*/

