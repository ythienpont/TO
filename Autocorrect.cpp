#include "Autocorrect.h"

Autocorrect::Autocorrect() {
    auto mainDFA = new DFA("");
}

// Main loop
void Autocorrect::run() {
    bool lessGo = true;

    while (lessGo) {
        std::cout << "Type 'quit' to quit...\nInput: ";
        std::string input;
        cin >> input;

        if (input == "quit") {
            lessGo = false;
            break;
        }
    }
}

void Autocorrect::inlezen() {
    string regex;
    char symb;
    cout << "De regexen worden nu ingelezen. U kunt het programma stoppen door bij de regex prompt 'stop' in te geven." << endl;
    while(regex != "stop") {
        cout << "Geef een regex in aub: ";
        cin >> regex;
        cout << "Geef het epsilon symbool in aub: ";
        cin >> symb;

        RE tempRE(regex, symb);
        listRegex.push_back(tempRE);
    }
    cout << "Alle regexen zijn ingelezen."<<endl;

}

void Autocorrect::autocorrect1(const string& theString)  {
    vector<string> correctedWords = mainDFA->autocorrect1(theString);
    if(correctedWords[0] == theString) cout << "De string '" << theString<<"' wordt aanvaard!"<<endl;
    else {
        cout << "origineel woord: -verbeterd woord 1- -verbeterd woord 2- ..." << endl;
        cout << theString << ": ";
        for (const auto &a: correctedWords) {
            cout << '-' << a << "- ";
        }
        cout << endl;
    }
}

void Autocorrect::autocorrect2(const string& theString) {

}

void Autocorrect::generateWord() {
    string random = mainDFA->randomWord();
    cout << "random word: "<< random << endl;
}


