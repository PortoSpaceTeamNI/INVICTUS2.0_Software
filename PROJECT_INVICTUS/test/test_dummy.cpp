#include <unity.h>
#include <Arduino.h>

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void test_dummy(void) {
    TEST_ASSERT_EQUAL(1, 1);
}

void setup() {
    UNITY_BEGIN();
    RUN_TEST(test_dummy);
    UNITY_END();
}

void loop() {
}
