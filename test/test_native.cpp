#include "unity.h"

void setUp(void)
{
    // set stuff up here
}

void tearDown(void)
{
    // clean stuff up here
}

void test_basic_math(void)
{
    TEST_ASSERT_EQUAL(5, 2 + 3);
}

void test_string_comparison(void)
{
    TEST_ASSERT_EQUAL_STRING("hello", "hello");
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_basic_math);
    RUN_TEST(test_string_comparison);
    return UNITY_END();
}