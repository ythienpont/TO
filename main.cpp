#include "NFA.h"
#include "RE.h"
#include "Autocorrect.h"
#include <time.h>
using namespace std;

int main() {
    srand(time(0));

    Autocorrect a;
    a.run();

   return 0;
}
