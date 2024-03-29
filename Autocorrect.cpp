#include "Autocorrect.h"
    using namespace std;


void hernaam(DFA& d){
    map<string,State*> aa = d.getStates();
    map<string,State*> newMap;

    map<string,string> replace;
    int m=0;
    for(auto& k : aa){
        string str;

        str =  to_string(m);

        replace[k.first] = str;
        k.second->setName(str);
        newMap[str] = k.second;
        m++;
    }

    for(auto& q : aa){

        map<char, vector<string>> newT;
        for(const auto& p: q.second->getTransitions()){
            vector<string> newV;
            for(const auto& f: p.second){
                newV.push_back(replace[f]);
            }
            newT[p.first] = newV;
        }
        q.second->setTransitions(newT);
    }

    d.setStates(newMap);
};

    //https://stackoverflow.com/questions/6486289/how-can-i-clear-console
    void clear() {
    // CSI[2J clears screen, CSI[H moves the cursor to top-left corner
    std::cout << "\x1B[2J\x1B[H";
    }

    // Main loop

    void Autocorrect::run() {
        cout << "----------START OF AUTOCORRECT PROJECT----------"<<endl<<endl;
        clear();
        generateWordlist();
        clear();

        bool running = true;
        while (running) {
            std::cout << "What do you want to do?" << std::endl;
            std::cout << "1. Input a word 2. Generate a word 3. Stop (1/2/3): ";
            int choice;
            cin >> choice;

            switch(choice) {
                case 1: {
                            std::cout << "Write a word: ";
                            std::string word;
                            cin >> word;
                            correct(word);
                            break;
                        }
                case 2: {
                            std::cout << "The generated word is " << generateWord() << std::endl;
                            break;
                        }
                default: {
                             cout << endl<<"GOODBYE :)" <<endl;
                             return;
                             //running = false;
                             //break;
                         }
            }
            std::cout << std::endl<< "Type anything to continue... ";
            std::string anything;
            cin >> anything;
            clear();
            }
        }

    void Autocorrect::generateWordlist() {
        int choice;

        std::cout << "How do you want to make the list of words?" << std::endl;
        std::cout << "1. From a file 2. Submit words yourself (1/2): ";
        cin >> choice;

        switch(choice) {
            case 1: {
                std::string fin;
                std::cout << "File: ";
                cin >> fin;
                readFile(fin);
                break;
            }
               
            default: {
                std::vector<std::string> words;
                std::string input;


                cout << "The words are being read. You can stop the program by entering 'stop'." << endl;
                while(true) {
                    cout << "Write a word: ";
                    cin >> input;
                    if(input == "stop"){
                    break;
                    }
                    words.push_back(input);
                }
                cout << "Give the epsilon symbol: ";
                cin >> epsChar;

                cout << "All words have been read."<<endl;

                if(words.size() > 0) {
                std::string REString = words[0];
                for (int i = 1; i < (int) words.size(); i++) {
                    REString += '+';
                    REString += words[i];
                }

                RE theRE(REString, epsChar);
                mainDFA = theRE.toDFA();
                break;
                }
             }
        }
    }

    void Autocorrect::readFile(const std::string &fin) {
    std::ifstream input(fin);
    if(!input.is_open()){
        cerr << "The file: "<< fin<< " doesn't exist!"<<endl;
        return;
    }
    json j;
    input >> j;

    std::string epsString = j["epsilon"];
    epsChar = epsString.at(0);

    std::vector<std::string> words;

    for (json::iterator it = j["wordlist"].begin(); it != j["wordlist"].end(); ++it) {
        std::string word = it->get<std::string>();
        words.push_back(word);
    }

    if(words.size() > 0) {
        std::string REString = words[0];
        for (int i = 1; i < (int) words.size(); i++) {
            REString += '+';
            REString += words[i];
        }

        RE theRE(REString, epsChar);
        DFA dfa = theRE.toDFA();
        mainDFA = dfa;
    } else {
        std::cerr << "The wordlist is empty\n";
    }
}

void Autocorrect::correct(const string& theString)  {
    vector<string> correctedWords = mainDFA.autocorrect1(theString);
    if(correctedWords[0] == theString) cout << "The string '" << theString<<"' is accepted!"<<endl;
    else {
        cout << "Input word: -corrected word 1- -corrected word 2- ..." << endl;
        cout << theString << ": ";
        for (const auto &a: correctedWords) {
            cout << '-' << a << "- ";
        }

        std::cout <<"Do you want to add this word to the list? (yes/no): ";
        std::string answer;
        cin >> answer;
        
        if (answer == "yes" or answer == "Yes" or answer == "y" or answer == " yes" or answer == "yes ") {
            RE newRE(theString, epsChar);
            DFA newDFA = newRE.toDFA();

            DFA newProduct(mainDFA,newDFA, false);
            mainDFA = newProduct;
        }
        cout << endl;
    }
}

std::string Autocorrect::generateWord() {
    return mainDFA.randomWord();
}


