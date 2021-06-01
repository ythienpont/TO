#include "NFA.h"
#include "RE.h"
#include "Autocorrect.h"
#include <ctime>
using namespace std;

int main() {
    srand(time(NULL));

    Autocorrect a;
    a.run();

   return 0;
}
