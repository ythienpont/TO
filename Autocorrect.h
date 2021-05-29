#ifndef AUTOCORRECT_AUTOCORRECT_H
#define AUTOCORRECT_AUTOCORRECT_H

#include "RE.h"

class Autocorrect {
    DFA mainDFA;
    char epsChar;
public:
    Autocorrect() : mainDFA("") {  };
    void run();
    void readFile(const std::string &fin);

    void correct(const std::string &string);
    void generateWord();
};
#endif //AUTOCORRECT_AUTOCORRECT_H
