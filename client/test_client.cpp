#define BOOST_TEST_MODULE MyTest
#include <boost/test/included/unit_test.hpp>
#include "client.h"


//-------------------------------------------------------------
/**
 * bool testbit(byte b, int n);
 * Test case 1: test bit of number < 255.
 */
 BOOST_AUTO_TEST_CASE(test_testbit_01) {
    byte org = 102;
    BOOST_CHECK_EQUAL((testbit(org, 0)), 0);
    BOOST_CHECK_EQUAL((testbit(org, 1)), 1);
    BOOST_CHECK_EQUAL((testbit(org, 2)), 1);
    BOOST_CHECK_EQUAL((testbit(org, 3)), 0);
    BOOST_CHECK_EQUAL((testbit(org, 4)), 0);
    BOOST_CHECK_EQUAL((testbit(org, 5)), 1);
    BOOST_CHECK_EQUAL((testbit(org, 6)), 1);
    BOOST_CHECK_EQUAL((testbit(org, 7)), 0);
}

/**
 * bool testbit(byte b, int n);
 * Test case 2: all bit is 1.
 */
BOOST_AUTO_TEST_CASE(test_testbit_02) {
    byte org = 255;
    BOOST_CHECK_EQUAL((testbit(org, 0)), 1);
    BOOST_CHECK_EQUAL((testbit(org, 1)), 1);
    BOOST_CHECK_EQUAL((testbit(org, 2)), 1);
    BOOST_CHECK_EQUAL((testbit(org, 3)), 1);
    BOOST_CHECK_EQUAL((testbit(org, 4)), 1);
    BOOST_CHECK_EQUAL((testbit(org, 5)), 1);
    BOOST_CHECK_EQUAL((testbit(org, 6)), 1);
    BOOST_CHECK_EQUAL((testbit(org, 7)), 1);
}

/**
 * bool testbit(byte b, int n);
 * Test case 3: all bit is 1.
 */
 BOOST_AUTO_TEST_CASE(test_testbit_03) {
    byte org = 90;
    BOOST_CHECK_EQUAL((testbit(org, 0)), 0);
    BOOST_CHECK_EQUAL((testbit(org, 1)), 1);
    BOOST_CHECK_EQUAL((testbit(org, 2)), 0);
    BOOST_CHECK_EQUAL((testbit(org, 3)), 1);
    BOOST_CHECK_EQUAL((testbit(org, 4)), 1);
    BOOST_CHECK_EQUAL((testbit(org, 5)), 0);
    BOOST_CHECK_EQUAL((testbit(org, 6)), 1);
    BOOST_CHECK_EQUAL((testbit(org, 7)), 0);
}

/**
 * bool testbit(byte b, int n);
 * Test case 4: all bit is 0.
 */
 BOOST_AUTO_TEST_CASE(test_testbit_04) {
    byte org = 0;
    BOOST_CHECK_EQUAL((testbit(org, 0)), 0);
    BOOST_CHECK_EQUAL((testbit(org, 1)), 0);
    BOOST_CHECK_EQUAL((testbit(org, 2)), 0);
    BOOST_CHECK_EQUAL((testbit(org, 3)), 0);
    BOOST_CHECK_EQUAL((testbit(org, 4)), 0);
    BOOST_CHECK_EQUAL((testbit(org, 5)), 0);
    BOOST_CHECK_EQUAL((testbit(org, 6)), 0);
    BOOST_CHECK_EQUAL((testbit(org, 7)), 0);
}

//--------------------------------------------------------------

/**
 * void onbit(byte b, int i);
 * Test case 1: turn on 1 bit
 */
 BOOST_AUTO_TEST_CASE(test_onbit_01) {
    byte org = 0;
    onbit(org, 4);
    byte des = 16;
    BOOST_CHECK_EQUAL(org, des);
}

/**
 * void onbit(byte b, int i);
 * Test case 2: turn on 2 bit
 */
 BOOST_AUTO_TEST_CASE(test_onbit_02) {
    byte org = 0;
    onbit(org, 4);
    onbit(org, 1);
    byte des = 18;
    BOOST_CHECK_EQUAL(org, des);
}

/**
 * void onbit(byte b, int i);
 * Test case 3: turn on bit 1
 */
 BOOST_AUTO_TEST_CASE(test_onbit_03) {
    byte org = 255;
    onbit(org, 4);
    byte des = 255;
    BOOST_CHECK_EQUAL(org, des);
}

/**
 * void onbit(byte b, int i);
 * Test case 1: turn on random bit
 */
 BOOST_AUTO_TEST_CASE(test_onbit_04) {
    byte org = 0;
    onbit(org, 4);
    onbit(org, 3);
    byte des = 24;
    BOOST_CHECK_EQUAL(org, des);
}

//--------------------------------------------------------------

/**
 * void arr_onbit(byte *a, int i, int size_a);
 * Test case 0: turn on single bit
 */
BOOST_AUTO_TEST_CASE(test_arr_onbit_01) {
    byte org[2] = {0, 0};
    arr_onbit(org, 0);
    BOOST_CHECK_EQUAL(org[0], 1);
    BOOST_CHECK_EQUAL(org[1], 0);
}

/**
 * void arr_onbit(byte *a, int i, int size_a);
 * Test case 1: multi bit on in first byte
 */
 BOOST_AUTO_TEST_CASE(test_arr_onbit_02) {
    byte org[2] = {0, 0};
    arr_onbit(org, 0);
    arr_onbit(org, 1);
    arr_onbit(org, 4);

    BOOST_CHECK_EQUAL(org[0], 19);
    BOOST_CHECK_EQUAL(org[1], 0);
}

/**
 * void arr_onbit(byte *a, int i, int size_a);
 * Test case 0: turn on multi bit in other byte
 */
 BOOST_AUTO_TEST_CASE(test_arr_onbit_03) {
    byte org[2] = {0, 0};
    arr_onbit(org, 0);
    arr_onbit(org, 8);
    BOOST_CHECK_EQUAL(org[0], 1);
    BOOST_CHECK_EQUAL(org[1], 1);
}

//--------------------------------------------------------------

