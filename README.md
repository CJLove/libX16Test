# libX16Test - a unit testing framework for using CC65 on the Commander X16

libX16Test is a unit test framework patterned after [googletest](https://github.com/google/googletest) and leveraging some ideas from [x16-testframework](https://github.com/hasenbanck/x16-testframework) for unit testing C code targeting the [Commander X16](http://commanderx16.com/).

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

    // TEST_EXIT    - exit the emulator on completion of tests
    // TEST_NO_EXIT - do not exit the emulator
    return x16testmain(TEST_EXIT);
}
```

Unit test programs should link against the `libX16Test.lib` library.

## Running unit tests
Unit test programs can be run manually in the emulator (likely with the `-echo` option).  

Unit test program can also be run via the `runTest.py` script which will run the emulator (optionally headless via `xvfb-run`), display unit test output as displayed inside the emulator, and exit with a return code indicating test PASS (return code 0) or FAIL (return code 1).  Examples of running the sample unit test program in the `example` directory:

```bash
# Manually run unit tests in the emulator:
x16emu -prg factorial_test.prg -run -echo

# Automated unit tests via script:
./bin/runTest.py --prg factorial_test.prg --xvfb
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
### Logical comparisons
Arguments can be an integer type or a pointer type, where a non-`NULL` value is considered to be TRUE:
* `EXPECT_TRUE(cond)` - test whether a condition is true (non-zero)
* `EXPECT_FALSE(cond)` - test whether condition is false (zero)
### Integer comparisions
Both arguments should be constants or integer types:
* `EXPECT_EQ(a,b)` - test whether two values are equal
* `EXPECT_NEQ(a,b)` - test whether two values are not equal
* `EXPECT_GT(a,b)` - test whether a is > b
* `EXPECT_GE(a,b)` - test whether a is >= b
* `EXPECT_LT(a,b)` - test whether a is < b
* `EXPECT_LE(a,b)` - test whether a is <= b
### String comparisons
Arguments can be string literals or `char *` C-style strings.
* `EXPECT_STREQ(a,b)` - test whether two strings are equal per `strcmp()`. 
* `EXPECT_STRNEQ(a,b)` - test whether two strings are not equal per `strcmp()`.
### VERA tests
* TBD

### Banked RAM tests
* TBD