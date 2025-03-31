#include <stdlib.h>
#include <time.h>
#include <unity.h>
#include <communications.h>

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void test_dummy(void) {
    TEST_ASSERT_EQUAL(1, 1);
}

int run_tests(void) {
    UNITY_BEGIN();
    RUN_TEST(test_dummy);
    return UNITY_END();
}

int main(void) {
    srand(time(NULL)); // Needed to generate mocks, can only be called once
    return run_tests();    
}
