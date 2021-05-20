//
// Created by Alperen on 13/02/2021.
//

#include "DFA.h"
#include <queue>

DFA::DFA(const string &fn) {//fn = filename
    ifstream input(fn);
    json j;
    input >> j;
    type = j["type"];
    vector<string> temp = j["alphabet"];
    alphabet = temp; // voor een of andere reden, geeft het een foutmelding als ik dit direct initialiseer

    for (auto i : j["states"]) {
        Node *knoop = new Node();
        knoop->naam = i["name"];
        knoop->final = i["accepting"];
        if (i["starting"])start = knoop;
        centralUnit[i["name"]] = knoop;
    }
    setTransitions(j);
}

void DFA::setTransitions(json j) {
    for (auto k : centralUnit) {
        for (auto q : j["transitions"]) {
            if (q["from"] == k.first) {
                k.second->pointers[q["input"]].push_back(centralUnit[q["to"]]);
            }
        }
    }
}


bool DFA::accepts(const string &str) const {
    Node *hP = start; // hP == huidige Pointer
    for (auto sym : str) { // sym = symbool
        hP = hP->pointers[string(1, sym)][0];
    }

    if (hP->final) {
        return true;
    } else {
        return false;
    }
}

void DFA::print() const {
    json j;
    j["type"] = type;
    j["alphabet"] = alphabet;
    int i = 0;
    int k = 0;
    for (const auto &state : centralUnit) {
        j["states"][i]["name"] = state.second->naam;

        if (state.second == start) {
            j["states"][i]["starting"] = true;
        } else {
            j["states"][i]["starting"] = false;
        }

        j["states"][i]["accepting"] = state.second->final;
        for (const auto &tr : state.second->pointers) {
            for (auto h: tr.second) {
                j["transitions"][k]["from"] = state.second->naam;
                j["transitions"][k]["to"] = h->naam;
                j["transitions"][k]["input"] = tr.first;

                k++;
            }
        }
        i++;
    }
    cout << setw(4) << j << endl;
}

vector<string> DFA::getStates() const {
    vector<string> key;
    for (const auto& cu : centralUnit) { // lijst met alle staten
        key.push_back(cu.first);
    }
    sort(key.begin(), key.end());
    return key;
}

vector<vector<bool>> DFA::mainKruisjes() {
    vector<string> key = getStates();

    vector<int> finalStates; // final states parsen
    for (int x = 0; x < key.size(); x++) {
        if (centralUnit[key[x]]->final) {
            finalStates.push_back(x);
        }
    }

    vector<vector<bool>> main;
    queue<pair<int, int>> kruisjes;

    for (int x = 0; x < key.size(); x++) {
        vector<bool> rij;
        for (int y = 0; y < key.size(); y++) {
            rij.push_back(false);
        }
        main.push_back(rij);
    }

    for (int i = 1; i < key.size(); i++) { // final state kruisjes
        vector<bool> temp;
        for (int m = 0; m < i; m++) {
            if (find(finalStates.begin(), finalStates.end(), i) == finalStates.end()
                xor find(finalStates.begin(), finalStates.end(), m) == finalStates.end()) {
                main[i][m] = true;
                kruisjes.push(make_pair(i, m));
            }
        }
    }
    cout << 7;

    //andere kruisjes
    while (!kruisjes.empty()) {
        string s1 = key[kruisjes.front().first];
        string s2 = key[kruisjes.front().second];
        kruisjes.pop();

        for (const auto &a : alphabet) {
            for (const auto& st1 : centralUnit) {
                if (st1.second->pointers[a][0]->naam == s1) {
                    for (const auto& st2 : centralUnit) {
                        if (st2.second->pointers[a][0]->naam == s2) {
                            int i1 = find(key.begin(), key.end(), st1.second->naam) - key.begin();
                            int i2 = find(key.begin(), key.end(), st2.second->naam) - key.begin();

                            if (!main[i1][i2]) {// nieuw kruisje, toegevoegd
                                kruisjes.push(make_pair(i1, i2));
                            }

                            main[i1][i2] = true;
                        }
                    }
                }
            }
        }
    }
    cout << 8;
    return main;
}

string benaam(vector<string> &vstr) {
    string str;
    for (const auto &c: vstr) {
        str += c;
    }
    sort(str.begin(), str.end()); // de string sorteren
    string staat = "{";

    for (const auto &c:str) {
        staat = staat + c + ", ";
    }

    staat = staat.substr(0, staat.size() - 2);
    staat += "}";
    return staat;
}

string benaam(string str) {
    sort(str.begin(), str.end()); // de string sorteren
    string staat = "{";

    for (const auto &c:str) {
        staat = staat + c + ", ";
    }

    staat = staat.substr(0, staat.size() - 2);
    staat += "}";
    return staat;
}

bool stringInVectoredVector(string str, vector<vector<string>> vec) {
    for (auto a : vec) {
        for (auto b : a) {
            if (b == str) {
                return true;
            }
        }
    }
    return false;
}

DFA DFA::minimize() {
    vector<vector<bool>> main = mainKruisjes();
    vector<string> key = getStates();

    vector<pair<string, string>> idStates; // indistinguishable states

    for (int i = 1; i < key.size(); i++) {
        for (int m = 0; m < i; m++) {
            if (!main[i][m]) {
                idStates.push_back({key[i], key[m]});
            }
        }
    }

    vector<vector<string>> states; // als A en C , B en C id zijn. Dan moeten A B en C samen een nieuwe staat worden

    for (const auto &a: idStates) {
        bool vlag = false;
        for (auto &id: states) {
            if (find(id.begin(), id.end(), a.first) != id.end()
                and find(id.begin(), id.end(), a.second) == id.end()) {
                id.push_back(a.second);
                vlag = true;
                break;
            } else if (find(id.begin(), id.end(), a.first) == id.end()
                       and find(id.begin(), id.end(), a.second) != id.end()) {
                id.push_back(a.first);
                vlag = true;
                break;
            }
            else if(find(id.begin(), id.end(), a.first) != id.end()
                    and find(id.begin(), id.end(), a.second) != id.end()) {
                vlag = true;
                break;
            }
        }
        if (!vlag) { // de staat is nog niet toegevoegd aan de nieuwe opslag
            vector<string> temp;
            temp.push_back(a.first);
            temp.push_back(a.second);

            states.push_back(temp);
        }
    }

    //nu hebben we vectoren die staten bevatten die ononderscheidbaar zijn
    DFA mDFA;
    mDFA.alphabet = alphabet;

    vector<tuple<Node *, string, string>> tempVec; // hierin slaan we transities in naar nodes die nog niet zijn aangemaakt

    map<string, Node *> newStates;
    for (vector<string> &s : states) { // de nieuwe knopen initialiseren
        string staatnaam = benaam(s);
        Node *kn = new Node();
        kn->naam = staatnaam;
        kn->final = false;

        for (const auto &c : s) {
            if (centralUnit[c]->final) {
                kn->final = true;
            }
            newStates[c] = kn;
        }

        for (auto a : alphabet) {
            if (find(s.begin(), s.end(), centralUnit[s[0]]->pointers[a][0]->naam)
            != s.end()) { // de knoop wijst naar zichzelf
                kn->pointers[a].push_back(kn);
            } else {
                if (stringInVectoredVector(centralUnit[s[0]]->pointers[a][0]->naam,
                                           states)) { // de knoop wijst naar een andere nieuwe staat
                    tempVec.push_back(make_tuple(kn, a, centralUnit[s[0]]->pointers[a][0]->naam));

                } else {
                    tempVec.push_back(make_tuple(kn, a, centralUnit[s[0]]->pointers[a][0]->naam));
                }
            }
        }
        mDFA.centralUnit[staatnaam] = kn;
    }


    for (auto st : centralUnit) { // andere knopen initialiseren
        if (newStates[st.first]) {
            continue; // deze knoop is al aangemaakt
        }

        Node *newNode = new Node();
        newNode->final = st.second->final;
        newNode->naam = benaam(st.second->naam);
        mDFA.centralUnit[st.second->naam] = newNode;

        for (const auto &a : alphabet) {
            if (newStates[st.second->pointers[a][0]->naam]) {
                newNode->pointers[a].push_back(newStates[st.second->pointers[a][0]->naam]);
            } else {
                if (mDFA.centralUnit[st.second->pointers[a][0]->naam]) {
                    newNode->pointers[a].push_back(mDFA.centralUnit[st.second->pointers[a][0]->naam]);
                } else {// de node waar de huidige node heengaat, is nog niet aangemaakt.
                    // We regelen deze transitie achteraf.
                    tempVec.push_back(make_tuple(newNode, a, st.second->pointers[a][0]->naam));
                }
            }
        }
    }

    for (auto f : tempVec) { // regelen van transities naar knopen die nog niet aangemaakt waren
        if(!mDFA.centralUnit[get<2>(f)]){
            mDFA.centralUnit.erase(get<2>(f));
            get<0>(f)->pointers[get<1>(f)].push_back(newStates[get<2>(f)]);
        }
        else {
            get<0>(f)->pointers[get<1>(f)].push_back(mDFA.centralUnit[get<2>(f)]);
        }
    }

    //start staat
    if (newStates[start->naam]) {
        mDFA.start = newStates[start->naam];
    } else {
        mDFA.start = mDFA.centralUnit[start->naam];
    }

    return mDFA;
}

void DFA::printTable() {
    vector<string> key = getStates();
    vector<vector<bool>> main = mainKruisjes();

    for (int i = 1; i < key.size(); i++) { // uitvoer
        cout << key[i] << "\t";
        for (int m = 0; m < i; m++) {
            if (main[i][m]) {
                cout << 'X';
            } else {
                cout << '-';
            }
            cout << "\t";
        }
        cout << endl;
    }
    for (int i = 0; i < key.size() - 1; i++) {
        cout << "\t" << key[i];
    }
    cout << endl;
}

bool DFA::operator==(DFA dfa2) {
    for (const auto& s : centralUnit) { // staten achteraan toevoegen
        dfa2.centralUnit[s.first] = s.second;
    }
    dfa2.printTable();

    vector<vector<bool>> main = dfa2.mainKruisjes();
    vector<string> key = dfa2.getStates();

    int is1 = find(key.begin(), key.end(), dfa2.start->naam) - key.begin(); // index start 2
    int is2 = find(key.begin(), key.end(), this->start->naam) - key.begin(); // index start 1

    if (main[is1][is2]) { // er staat een kruisje op de start staten intersectie
        return false;
    } else {
        return true;
    }
}
