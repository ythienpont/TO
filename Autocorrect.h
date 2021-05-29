#ifndef AUTOCORRECT_AUTOCORRECT_H
#define AUTOCORRECT_AUTOCORRECT_H

#include "RE.h"

class Autocorrect {
    DFA mainDFA;
public:
    Autocorrect() : mainDFA("") {  };
    void run();
    void readFile(const std::string &fin);

    void autocorrect1(const std::string &string);
    void autocorrect2(const std::string &string);
    void generateWord();
};
#endif //AUTOCORRECT_AUTOCORRECT_H
