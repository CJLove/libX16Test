#ifndef X16_TEST
#define X16_TEST

#include <stdint.h>
#include <stdio.h>
#include <string.h>

typedef int (*TestModulePtr)(void);

#define TEST_EXIT 0
#define TEST_NO_EXIT 1

extern int x16testmain(uint8_t noExit);

extern void registerTestModule(TestModulePtr funcPtr, char* moduleName);

#define TEST_INIT()    \
    uint8_t tests = 0; \
    uint8_t failures = 0;

#define TEST_COMPLETE()                                      \
    printf("    tests: %d failures: %d\n", tests, failures); \
    printf("===============\n");                             \
    return (failures != 0);

#define EXPECT_TRUE(a)                                             \
    {                                                              \
        tests++;                                                   \
        if (!(a)) {                                                \
            failures++;                                            \
            printf("failure at %s line %d\n", __FILE__, __LINE__); \
        }                                                          \
    }

#define EXPECT_FALSE(a)                                            \
    {                                                              \
        tests++;                                                   \
        if ((a)) {                                                 \
            failures++;                                            \
            printf("failure at %s line %d\n", __FILE__, __LINE__); \
        }                                                          \
    }

#define EXPECT_EQ(a, b)                                                                \
    {                                                                                  \
        tests++;                                                                       \
        if ((a) != (b)) {                                                              \
            failures++;                                                                \
            printf("failure at l%s ine %d: %u != %u\n", __FILE__, __LINE__, (a), (b)); \
        }                                                                              \
    }

#define EXPECT_NEQ(a, b)                                                               \
    {                                                                                  \
        tests++;                                                                       \
        if ((a) == (b)) {                                                              \
            failures++;                                                                \
            printf("failure at %s line %d: %u == %u\n", __FILE__, __LINE__, (a), (b)); \
        }                                                                              \
    }

#define EXPECT_GT(a, b)                                                                \
    {                                                                                  \
        tests++;                                                                       \
        if ((a) <= (b)) {                                                              \
            failures++;                                                                \
            printf("failure at %s line %d: %u <= %u\n", __FILE__, __LINE__, (a), (b)); \
        }                                                                              \
    }

#define EXPECT_GE(a, b)                                                               \
    {                                                                                 \
        tests++;                                                                      \
        if ((a) < (b)) {                                                              \
            failures++;                                                               \
            printf("failure at %s line %d: %u < %u\n", __FILE__, __LINE__, (a), (b)); \
        }                                                                             \
    }

#define EXPECT_LT(a, b)                                                                \
    {                                                                                  \
        tests++;                                                                       \
        if ((a) >= (b)) {                                                              \
            failures++;                                                                \
            printf("failure at %s line %d: %u >= %u\n", __FILE__, __LINE__, (a), (b)); \
        }                                                                              \
    }

#define EXPECT_LE(a, b)                                                               \
    {                                                                                 \
        tests++;                                                                      \
        if ((a) > (b)) {                                                              \
            failures++;                                                               \
            printf("failure at %s line %d: %u > %u\n", __FILE__, __LINE__, (a), (b)); \
        }                                                                             \
    }

#define EXPECT_STREQ(a, b)                                                                     \
    {                                                                                          \
        tests++;                                                                               \
        if (strcmp((a), (b))) {                                                                \
            failures++;                                                                        \
            printf("failure at %s line %d: \"%s\" != \"%s\"\n", __FILE__, __LINE__, (a), (b)); \
        }                                                                                      \
    }

#define EXPECT_STRNEQ(a, b)                                                                    \
    {                                                                                          \
        tests++;                                                                               \
        if (strcmp((a), (b)) == 0) {                                                           \
            failures++;                                                                        \
            printf("failure at %s line %d: \"%s\" == \"%s\"\n", __FILE__, __LINE__, (a), (b)); \
        }                                                                                      \
    }

#endif