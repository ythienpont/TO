#include "NFA.h"
#include "RE.h"
#include "Autocorrect.h"
#include <time.h>
using namespace std;

void hernaam(DFA& d){
    map<string,State*> aa = d.getStates();
    map<string,State*> newMap;

    map<string,string> replace;
    int m=0;
    for(auto& k : aa){
        string str;
        /*if(k.first == "DEAD"){
            str = "{DEAD}";
            m--;
        }
        else{*/
            str =  to_string(m);
        //}
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

int main() {
    DFA dfa("temp.json");
    map<string,State*> aa = dfa.getStates();
   //hernaam(dfa);

    //hernaam("1", dfa.getStartState()->getName(), dfa);
    //for(auto d: dfa)
    //hernaam("1", dfa.getStartState()->getName(), dfa);
    //dfa = dfa.minimize();
    dfa = dfa.minimize();
    //dfa = dfa.minimize();
    dfa.print();

    /*srand(time(0));

    Autocorrect a;
    a.readFile("words.json");
    //a.run();*/
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
   //
   /*RE re1("DFA", '%');
   RE re2("NFA", '%');

   DFA dfa1 = re1.toDFA();
   DFA dfa2 = re2.toDFA();
   DFA dfa3(dfa1,dfa2,true);*/
   //dfa3.print();



   return 0;
}
