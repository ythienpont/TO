#include "Autocorrect.h"
using namespace std;

// Main loop

void Autocorrect::run() {
    std::vector<RE> listRegex;
    std::vector<std::string> inputStrings;
    std::string input;
    //char eps;

    bool running = true;

    cout << "De woorden worden nu ingelezen. U kunt het programma stoppen door 'stop' in te geven." << endl;
    while(running) {
        cout << "Geef een woord in: ";
        cin >> input;
        if(input == "stop"){
            running = false;
            break;
        }

        correct(input);
    }    

    cout << "Alle woorden zijn ingelezen."<<endl;

    cout << "Geef het epsilon symbool in: ";
    cin >> epsChar;

    for (auto i:inputStrings) {
        RE theRE(i, epsChar);
        listRegex.push_back(theRE);
    }


    // hier worden de regexen samengevoegd
    // ...
}

void Autocorrect::readFile(const std::string &fin) {
    std::ifstream input(fin);
    json j;
    input >> j;

    std::string epsString = j["epsilon"];
    char epsChar = epsString.at(0);

    std::vector<std::string> words;

    for (json::iterator it = j["wordlist"].begin(); it != j["wordlist"].end(); ++it) {
        std::string word = it->get<std::string>();
        words.push_back(word);
    }

    if((int) words.size() > 0) {
        std::string REString = words[0];
        for (int i = 1; i < (int) words.size(); i++) {
            REString += '+';
            REString += words[i];
        }
        std::cout << REString << std::endl;

        RE theRE(REString, epsChar);
        mainDFA = theRE.toDFA();
    } else {
        std::cerr << "The wordlist is empty\n";
    }
}

void Autocorrect::correct(const string& theString)  {
    vector<string> correctedWords = mainDFA.autocorrect1(theString);
    if(correctedWords[0] == theString) cout << "De string '" << theString<<"' wordt aanvaard!"<<endl;
    else {
        cout << "origineel woord: -verbeterd woord 1- -verbeterd woord 2- ..." << endl;
        cout << theString << ": ";
        for (const auto &a: correctedWords) {
            cout << '-' << a << "- ";
        }

        std::cout << "Do you want to add this word to the list? (yes/no): ";
        std::string answer;
        cin >> answer;
        
        if (answer == "yes" or answer == "Yes" or answer == "y" or answer == " yes" or answer == "yes ") {
            //Do something
            RE newRE(theString, epsChar);
            DFA newDFA = newRE.toDFA();

            DFA newProduct(mainDFA,newDFA, true);
            mainDFA = newProduct;
        }
        cout << endl;
    }
}

void Autocorrect::generateWord() {
    string random = mainDFA.randomWord();
    cout << "random word: "<< random << endl;
}


