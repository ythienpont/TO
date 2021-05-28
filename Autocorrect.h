#ifndef AUTOCORRECT_AUTOCORRECT_H
#define AUTOCORRECT_AUTOCORRECT_H

#include "RE.h"

class Autocorrect {
    DFA mainDFA;
public:
    void inlezen();
    void autocorrect1(const std::string &string);
    void autocorrect2(const std::string &string);
    void generateWord();
};
#endif //AUTOCORRECT_AUTOCORRECT_H
