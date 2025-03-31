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

void test_crc(void) {
    Packet packet;
    byte payload[5] = {1, 2, 3, 4, 5};
    create_packet(0x01, ID_MC_Telemetry, ID_R_Telemetry, 5, payload, &packet);
    TEST_ASSERT_TRUE(check_crc(&packet));
}

int run_tests(void) {
    UNITY_BEGIN();
    RUN_TEST(test_dummy);
    return UNITY_END();
}

int main(void) {
    return run_tests();    
}
