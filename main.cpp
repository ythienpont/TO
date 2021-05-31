#include "NFA.h"
#include "RE.h"
#include "Autocorrect.h"
#include <time.h>
using namespace std;


int main() {
    srand(time(0));
    //DFA dfa("input-tfa1.json");
    //DFA dfa2("dfatest.json");

    //DFA mindfa = dfa2.minimize();
    //dfa2.printTable();

    //cout << boolalpha << (mindfa == dfa2) << endl;    // zijn ze equivalent? Zou hier zeker moeten. Dit wordt getest in de volgende vraag, maar hiermee kan je al eens proberen
    
    /*
    RE re("(m+y)*+(e+y+m+i)s",'e');
    ENFA enfa = re.toENFA();
    RE re1("autom(a+en)",'z');
    ENFA enfa1 = re1.toENFA();
    RE re2("a*h",'e');
    ENFA enfa2 = re2.toENFA();
    enfa2.print();
    //enfa.print();
    */
    /*//geeft true
    cout << boolalpha << enfa.accepts("ys") << endl;
    cout << boolalpha << enfa.accepts("mmyyymmmym") << endl;
    cout << boolalpha << enfa.accepts("s") << endl;
    //geeft false
    cout << boolalpha << enfa.accepts("ss") << endl;
    cout << boolalpha << enfa.accepts("ims") << endl;
    cout << boolalpha << enfa.accepts("mimis") << endl;*/

   //NFA nfa("nfaFile1.json");
   //cout << "nfa accepts: " << nfa.accepts("c");

   Autocorrect a;

   a.readFile("words.json");


   a.mainDFA.minimize().print();

   a.run();

   return 0;
}
