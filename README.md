# libX16Test - a unit testing framework for using CC65 on the Commander X16

libX16Test is a unit test framework patterned after [googletest](https://github.com/google/googletest) and leveraging some implementation ideas from [x16-testframework](https://github.com/hasenbanck/x16-testframework) for unit testing C code targeting the [Commander X16](http://commanderx16.com/).

## Dependencies
* [CC65](https://github.com/cc65/cc65)
* Python3 for the script which runs test executables
* Optional: [xvfb](https://www.x.org/releases/X11R7.6/doc/man/man1/Xvfb.1.xhtml) (X Virtual Framebuffer) for running the x16 emulator "headless" on Linux

## Building the library
```bash
cd src
make
```

## Writing unit tests
Unit tests are organized into "modules" which are comprised of actual tests.  Modules can test a single C function or group of functions.

All modules are implemented as C functions matching the following signature:
```c
int testModule(void);
```

Modules are registered with libX16Test via the `registerModule()` function.  Unit tests are executed by calling the `x16testmain()` function.
```c
#include "x16test.h"

int myModule(void)
{
    ...
}

int main()
{
    registerModule(myModule,"myModuleName");

    return x16testmain(TEST_EXIT);
}
```

## Test module details
All test modules should begin with the `TEST_INIT()` call and end with the `TEST_COMPLETE()` call.  Other variable declarations can follow the `TEST_INIT()` call.  The following is an example test module testing a `factorial()` function:

```c
int testFactorial(void)
{
    TEST_INIT()

    EXPECT_EQ(1,factorial(0));
    
    EXPECT_EQ(1,factorial(1));

    EXPECT_EQ(2,factorial(2));

    EXPECT_EQ(6,factorial(3));

    EXPECT_EQ(24,factorial(4));

    TEST_COMPLETE()
}
```

## Test methods
* EXPECT_TRUE(cond) - test whether a condition is true (non-zero)
* EXPECT_FALSE(cond) - test whether condition is false (zero)
* EXPECT_EQ(a,b) - test whether two values are equal
* EXPECT_NEQ(a,b) - test whether two values are not equal
* EXPECT_GT(a,b) - test whether a is > b
* EXPECT_GE(a,b) - test whether a is >= b
* EXPECT_LT(a,b) - test whether a is < b
* EXPECT_LE(a,b) - test whether a is <= b
* EXPECT_STREQ(a,b) - test whether two strings are equal per `strcmp()`
* EXPECT_STRNEQ(a,b) - test whether two strings are not equal per `strcmp()`
* 