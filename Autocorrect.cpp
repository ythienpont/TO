
#include "Autocorrect.h"

void Autocorrect::inlezen() {
    string regex = " ";
    while(!regex.empty()) {
        cout << "Geef een regex in aub: ";
        cin >> regex;
        //RE tempRE(regex); // dit kan verder aangevuld worden wanneer de RE constructor is gemaakt
        //listRegex.push_back(tempRE);
    }
    cout << "Alle regexen zijn ingelezen."<<endl;

}

void Autocorrect::autocorrect1(DFA dfa) {

}

void Autocorrect::autocorrect2(DFA) {

}


