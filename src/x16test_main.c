#include "x16test.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

extern void __fastcall__ quit(uint8_t status);

struct testModule_t {
    char* moduleName;
    TestModulePtr funcPtr;
};

#define MAX_MODULES 500

struct testModule_t modules[MAX_MODULES];
uint16_t moduleIndex = 0;

void registerTestModule(TestModulePtr funcPtr, char* moduleName)
{
    modules[moduleIndex].moduleName = moduleName;
    modules[moduleIndex].funcPtr = funcPtr;
    moduleIndex++;
}

int x16testmain(uint8_t noExit)
{
    uint16_t idx = 0;
    uint16_t tests = 0;
    uint16_t failures = 0;
    printf("running %d test modules\n",moduleIndex);
    printf("===============\n");

    for (idx = 0; idx < moduleIndex; idx++) {
        int result = 0;
        printf("starting module %s\n",modules[idx].moduleName);
        result = modules[idx].funcPtr();
        printf("finished module %s\n",modules[idx].moduleName);
        tests++;
        if (result) {
            failures++;
        }
    }

    printf("test modules: %d module failures: %d\n",tests,failures);

    if (noExit)
        return (failures != 0);
    else
        quit (failures != 0);
}