#include "unity/unity.h"
#include "inc/Calculator.h"


// Hàm chạy trước mỗi test case
void setUp(void) {
    
}

// Hàm chạy sau mỗi test case
void tearDown(void) {
    
}

// Test case cho hàm add
void test_Addition(void) {
    TEST_ASSERT_EQUAL(6, add(2, 3));
    TEST_ASSERT_EQUAL(0, add(-2, 2));
}

// Test case cho hàm subtract
void test_Subtraction(void) {
    TEST_ASSERT_EQUAL(1, subtract(3, 2));
    TEST_ASSERT_EQUAL(-4, subtract(-2, 2));
}

// Test case cho hàm multiply
void test_Multiplication(void) {
    TEST_ASSERT_EQUAL(6, multiply(2, 3));
    TEST_ASSERT_EQUAL(-4, multiply(-2, 2));
}



int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_Addition);
    RUN_TEST(test_Subtraction);
    RUN_TEST(test_Multiplication);

    return UNITY_END();
}