#include "x16test.h"

extern uint16_t factorial(uint16_t);

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

int testComparisons(void)
{
    TEST_INIT()
    const char *strLiteral="anystring";

    EXPECT_TRUE(1);

    EXPECT_FALSE(0);

    EXPECT_NEQ(2,5);

    EXPECT_GT(5,4);

    EXPECT_GE(4,4);

    EXPECT_GE(5,4);

    EXPECT_LT(4,12);

    EXPECT_STREQ("anystring",strLiteral);

    EXPECT_STRNEQ("foo",strLiteral);

    TEST_COMPLETE()
}

int testComparisonFailures(void)
{
    TEST_INIT()
    const char *strLiteral="anyString";

    EXPECT_TRUE(0);

    EXPECT_FALSE(1);

    EXPECT_NEQ(2,2);

    EXPECT_GT(4,5);

    EXPECT_GE(4,5);

    EXPECT_LT(40,12);

    EXPECT_STREQ("anyOtherString",strLiteral);

    EXPECT_STRNEQ("anyString",strLiteral);

    TEST_COMPLETE()
}
