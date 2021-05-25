#include "NFA.h"
using namespace std;


int main() {
    DFA dfa("input-tfa1.json");
    DFA dfa2("dfatest.json");

    DFA mindfa = dfa2.minimize();
    //dfa.printTable();

   cout << boolalpha << (mindfa == dfa2) << endl;    // zijn ze equivalent? Zou hier zeker moeten. Dit wordt getest in de volgende vraag, maar hiermee kan je al eens proberen

   NFA nfa("nfaFile1.json");
   cout << "nfa accepts: " << nfa.accepts("c");
   return 0;
}
