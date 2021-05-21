//
// Created by Alperen on 13/02/2021.
//


#ifndef TA1_13_02_DFA_H
#define TA1_13_02_DFA_H

#include <iostream>
#include <fstream>
#include "json.hpp"
#include <iomanip>

using json = nlohmann::json;
using namespace std;

class Node {
public:
    string naam;
    map<string,vector<Node*>> pointers; //transities, bv 0,Q2
    bool final;
};

class DFA {
public:
    string type;
    vector<string> alphabet;
    Node* start;

    map<string,Node*> centralUnit; // string: naam staat    Node*: info over die staat
    void setTransitions(json j);

    vector<string> getStates() const; // krijg een lijst met alle staatnamen
    vector<vector<bool>> mainKruisjes() ; // krijg de tabel met kruisjes


    DFA () {type = "DFA";};
    DFA(const string& fn);
    bool accepts(const string&) const;
    void print() const;

    DFA minimize();
    void printTable();
    bool operator==(DFA);
};


#endif //TA1_13_02_DFA_H
