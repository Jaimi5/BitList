#include <unity.h>
#include "BitList.h"

void setUp(void) {
    // Set up code here, if needed
}

void tearDown(void) {
    // Clean up code here, if needed
}

void test_bit_list_initialization(void) {
    BitList bl(16);
    TEST_ASSERT_EQUAL(16, bl.getSize());
    TEST_ASSERT_EQUAL(0, bl.countBits());
}

void test_bit_list_add_and_get_bit(void) {
    BitList bl(16);
    bl.addBit(true);
    bl.addBit(false);
    bl.addBit(true);

    TEST_ASSERT_TRUE(bl.getBit(0));
    TEST_ASSERT_FALSE(bl.getBit(1));
    TEST_ASSERT_TRUE(bl.getBit(2));
    TEST_ASSERT_EQUAL(2, bl.countBits());
}

void test_bit_list_out_of_range(void) {
    BitList bl(16);
    try {
        bl.getBit(16);
        TEST_FAIL_MESSAGE("Expected out_of_range exception");
    }
    catch (const std::out_of_range& e) {
        TEST_ASSERT_TRUE(true);
    }
    catch (...) {
        TEST_FAIL_MESSAGE("Expected out_of_range exception");
    }
}

void test_bit_list_clear_and_reuse(void) {
    BitList bl(16);
    bl.addBit(true);
    bl.addBit(true);
    bl.addBit(true);

    TEST_ASSERT_EQUAL(3, bl.countBits());

    bl.clear();
    TEST_ASSERT_EQUAL(0, bl.countBits());
    TEST_ASSERT_EQUAL(16, bl.getSize());
}

void test_bit_list_full_cycle(void) {
    BitList bl(8);
    for (int i = 0; i < 8; ++i) {
        bl.addBit(i % 2 == 0);
    }

    for (int i = 0; i < 8; ++i) {
        TEST_ASSERT_EQUAL(i % 2 == 0, bl.getBit(i));
    }

    bl.addBit(true); // This should overwrite the first bit
    TEST_ASSERT_TRUE(bl.getBit(0));
}

void test_bit_list_goes_first_when_adding(void) {
    BitList bl(8);
    for (int i = 0; i < 8; ++i) {
        bl.addBit(i % 2 == 0);
    }

    for (int i = 0; i < 8; ++i) {
        TEST_ASSERT_EQUAL(i % 2 == 0, bl.getBit(i));
    }

    bl.addBit(true); // This should overwrite the first bit
    TEST_ASSERT_TRUE(bl.getBit(0));
    TEST_ASSERT_EQUAL(8 / 2, bl.countBits());
}

void test_bit_list_bigger_size(void) {
    BitList bl(256);
    for (int i = 0; i < 256; ++i) {
        bl.addBit(i % 2 == 0);
    }

    for (int i = 0; i < 256; ++i) {
        TEST_ASSERT_EQUAL(i % 2 == 0, bl.getBit(i));
    }

    bl.addBit(false); // This should overwrite the first bit
    TEST_ASSERT_FALSE(bl.getBit(0));
    TEST_ASSERT_EQUAL(256 / 2 - 1, bl.countBits());
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_bit_list_initialization);
    RUN_TEST(test_bit_list_add_and_get_bit);
    RUN_TEST(test_bit_list_out_of_range);
    RUN_TEST(test_bit_list_clear_and_reuse);
    RUN_TEST(test_bit_list_full_cycle);
    RUN_TEST(test_bit_list_goes_first_when_adding);
    RUN_TEST(test_bit_list_bigger_size);
    return UNITY_END();
}