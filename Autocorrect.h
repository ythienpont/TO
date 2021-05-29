#ifndef AUTOCORRECT_AUTOCORRECT_H
#define AUTOCORRECT_AUTOCORRECT_H

#include "RE.h"

class Autocorrect {
    char epsChar;
public:
    DFA mainDFA;
    Autocorrect() : mainDFA("") {  };
    void run();
    void generateWordlist();
    void readFile(const std::string &fin);

    void correct(const std::string &string);
    std::string generateWord();
};
#endif //AUTOCORRECT_AUTOCORRECT_H
