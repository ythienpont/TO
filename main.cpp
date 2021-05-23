#include "NFA.h"
using namespace std;


int main() {
    DFA dfa("../input-tfa1.json");
    DFA dfa2("../dfatest.json");
    //cout << dfa.start->naam<< 1 <<endl;

    DFA mindfa = dfa2.minimize();
 // t volgende geeft een foutmelding
 //cout << endl << endl << endl;
   cout << boolalpha << (mindfa == dfa2) << endl;    // zijn ze equivalent? Zou hier zeker moeten. Dit wordt getest in de volgende vraag, maar hiermee kan je al eens proberen
    return 0;
}


