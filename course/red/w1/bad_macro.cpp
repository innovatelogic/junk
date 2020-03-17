#include "test_runner.h"

#include <ostream>
using namespace std;

#define PRINT_VALUES(out, x, y) do {\
out << (x) << std::endl; out << (y) << std::endl;\
} while(0)


int main() {
    ostringstream output;
    if (1)
        PRINT_VALUES(output, 5, "red belt");
    else
        PRINT_VALUES(output, 5, "red belt");
    
 TestRunner tr;
  tr.RunTest([]
 {
    ostringstream output;
    PRINT_VALUES(output, 5, "red belt");
    ASSERT_EQUAL(output.str(), "5\nred belt\n");
  }, "PRINT_VALUES usage example");
}