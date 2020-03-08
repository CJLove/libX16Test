#include <stdio.h>
#include "x16test.h"

extern int testFactorial(void);
extern int testComparisons(void);
extern int testComparisonFailures(void);

int main()
{
    printf("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    registerTestModule(testFactorial,"factorial");
    registerTestModule(testComparisons, "comparisons");
    registerTestModule(testComparisonFailures, "comparisonFailures");

    return x16testmain(TEST_EXIT);
}