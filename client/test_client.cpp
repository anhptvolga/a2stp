#define BOOST_TEST_MODULE MyTest
#include <boost/test/included/unit_test.hpp>
#include "client.h"

BOOST_AUTO_TEST_CASE(test_testbit_00) {
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

BOOST_AUTO_TEST_CASE(test_testbit_01) {
    byte org = 3;
    BOOST_CHECK_EQUAL((testbit(org, 0)), 1);
    BOOST_CHECK_EQUAL((testbit(org, 1)), 1);
    BOOST_CHECK_EQUAL((testbit(org, 2)), 0);
    BOOST_CHECK_EQUAL((testbit(org, 3)), 0);
    BOOST_CHECK_EQUAL((testbit(org, 4)), 0);
    BOOST_CHECK_EQUAL((testbit(org, 5)), 0);
    BOOST_CHECK_EQUAL((testbit(org, 6)), 0);
    BOOST_CHECK_EQUAL((testbit(org, 7)), 0);
}