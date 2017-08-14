#define BOOST_TEST_MODULE BasicTestExample
#include <boost/test/auto_unit_test.hpp>
#include "../bitlib.h"

/* ----------------------------------------------- */
/* ------------Test Function testbit-------------- */
/* ----------------------------------------------- */
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
    byte org = 4;
    BOOST_CHECK_EQUAL((testbit(org, 0)), 0);
    BOOST_CHECK_EQUAL((testbit(org, 1)), 0);
    BOOST_CHECK_EQUAL((testbit(org, 2)), 1);
    BOOST_CHECK_EQUAL((testbit(org, 3)), 0);
    BOOST_CHECK_EQUAL((testbit(org, 4)), 0);
    BOOST_CHECK_EQUAL((testbit(org, 5)), 0);
    BOOST_CHECK_EQUAL((testbit(org, 6)), 0);
    BOOST_CHECK_EQUAL((testbit(org, 7)), 0);
}

BOOST_AUTO_TEST_CASE(test_testbit_02) {
    char org = 100;
    BOOST_CHECK_EQUAL((testbit(org, 0)), 0);
    BOOST_CHECK_EQUAL((testbit(org, 1)), 0);
    BOOST_CHECK_EQUAL((testbit(org, 2)), 1);
    BOOST_CHECK_EQUAL((testbit(org, 3)), 0);
    BOOST_CHECK_EQUAL((testbit(org, 4)), 0);
    BOOST_CHECK_EQUAL((testbit(org, 5)), 1);
    BOOST_CHECK_EQUAL((testbit(org, 6)), 1);
    BOOST_CHECK_EQUAL((testbit(org, 7)), 0);
    BOOST_CHECK_EQUAL((testbit(org, 8)), 0);
    BOOST_CHECK_EQUAL((testbit(org, 9)), 0);
    BOOST_CHECK_EQUAL((testbit(org, 10)), 0);
}

BOOST_AUTO_TEST_CASE(test_testbit_03) {
    char org = 127;
    BOOST_CHECK_EQUAL((testbit(org, 0)), 1);
    BOOST_CHECK_EQUAL((testbit(org, 1)), 1);
    BOOST_CHECK_EQUAL((testbit(org, 2)), 1);
    BOOST_CHECK_EQUAL((testbit(org, 3)), 1);
    BOOST_CHECK_EQUAL((testbit(org, 4)), 1);
    BOOST_CHECK_EQUAL((testbit(org, 5)), 1);
    BOOST_CHECK_EQUAL((testbit(org, 6)), 1);
    BOOST_CHECK_EQUAL((testbit(org, 7)), 0);
}

/* ----------------------------------------------- */
/* ---------------test function onbit------------- */
/* ----------------------------------------------- */
BOOST_AUTO_TEST_CASE(test_onbit_01) {
    char org = 0;
    onbit(org, 4);
    char exp = 16;
    BOOST_CHECK_EQUAL(org, exp);
}

BOOST_AUTO_TEST_CASE(test_onbit_02) {
    char org = 0;
    onbit(org, 4);
    onbit(org, 0);
    char exp = 17;
    BOOST_CHECK_EQUAL(org, exp);
}

BOOST_AUTO_TEST_CASE(test_onbit_03) {
    char org = 6;
    onbit(org, 1);
    onbit(org, 2);
    char exp = 6;
    BOOST_CHECK_EQUAL(org, exp);
}

/* ----------------------------------------------- */
/* ---------------test function arr_onbit------------- */
/* ----------------------------------------------- */
BOOST_AUTO_TEST_CASE(test_arr_onbit_01) {
    char org[2] = {12, 50};
    arr_onbit(org, 0, 2);
    BOOST_CHECK_EQUAL(org[0], 12);
    BOOST_CHECK_EQUAL(org[1], 51);
}


BOOST_AUTO_TEST_CASE(test_arr_onbit_02) {
    char org[5] = {0, 0, 0, 0, 0};
    arr_onbit(org, 8, 5);
    arr_onbit(org, 9, 5);
    arr_onbit(org, 10, 5);

    BOOST_CHECK_EQUAL(org[0], 0);
    BOOST_CHECK_EQUAL(org[1], 0);
    BOOST_CHECK_EQUAL(org[2], 0);
    BOOST_CHECK_EQUAL(org[3], 7);
    BOOST_CHECK_EQUAL(org[4], 0);
}

/* ----------------------------------------------- */
/* ---------------test function offbit------------- */
/* ----------------------------------------------- */
BOOST_AUTO_TEST_CASE(test_offbit_01) {
    char org = 6;
    offbit(org, 1);
    char exp = 4;
    BOOST_CHECK_EQUAL(org, exp);
}

BOOST_AUTO_TEST_CASE(test_offbit_02) {
    char org = 6;
    offbit(org, 1);
    offbit(org, 2);
    char exp = 0;
    BOOST_CHECK_EQUAL(org, exp);
}

BOOST_AUTO_TEST_CASE(test_offbit_03) {
    char org = 126;
    offbit(org, 10);
    onbit(org, 10);
    char exp = 126;
    BOOST_CHECK_EQUAL(org, exp);
}

/* ----------------------------------------------- */
/* ---------test function arr_testbit------------- */
/* ----------------------------------------------- */
BOOST_AUTO_TEST_CASE(test_arr_testbit_01) {
    char org[2] = { 10, 11 };
    int org_size = 2;
    //bin_print_char(30);
    //bin_print_buff(org, 2);
    BOOST_CHECK_EQUAL((arr_testbit(org, 0, org_size)), 1);
    BOOST_CHECK_EQUAL((arr_testbit(org, 1, org_size)), 1);
    BOOST_CHECK_EQUAL((arr_testbit(org, 2, org_size)), 0);
    BOOST_CHECK_EQUAL((arr_testbit(org, 3, org_size)), 1);

    BOOST_CHECK_EQUAL((arr_testbit(org, 8, org_size)), 0);
    BOOST_CHECK_EQUAL((arr_testbit(org, 9, org_size)), 1);
    BOOST_CHECK_EQUAL((arr_testbit(org, 10, org_size)), 0);
    BOOST_CHECK_EQUAL((arr_testbit(org, 11, org_size)), 1);
}

BOOST_AUTO_TEST_CASE(test_arr_testbit_02) {
    char org[2] = { 127, 11 };
    int org_size = 2;
    BOOST_CHECK_EQUAL((arr_testbit(org, 0, org_size)), 1);
    BOOST_CHECK_EQUAL((arr_testbit(org, 1, org_size)), 1);
    BOOST_CHECK_EQUAL((arr_testbit(org, 2, org_size)), 0);
    BOOST_CHECK_EQUAL((arr_testbit(org, 3, org_size)), 1);

    BOOST_CHECK_EQUAL((arr_testbit(org, 8, org_size)), 1);
    BOOST_CHECK_EQUAL((arr_testbit(org, 9, org_size)), 1);
    BOOST_CHECK_EQUAL((arr_testbit(org, 10, org_size)), 1);
    BOOST_CHECK_EQUAL((arr_testbit(org, 11, org_size)), 1);
    BOOST_CHECK_EQUAL((arr_testbit(org, 12, org_size)), 1);
    BOOST_CHECK_EQUAL((arr_testbit(org, 13, org_size)), 1);
    BOOST_CHECK_EQUAL((arr_testbit(org, 14, org_size)), 1);
    BOOST_CHECK_EQUAL((arr_testbit(org, 15, org_size)), 0);
}



BOOST_AUTO_TEST_CASE(test_arr_testbit_03) {
    char org[2] = { 10, 11 };
    int org_size = 2;
    BOOST_CHECK_EQUAL((arr_testbit(org, 0, org_size)), 1);
    BOOST_CHECK_EQUAL((arr_testbit(org, 1, org_size)), 1);
    BOOST_CHECK_EQUAL((arr_testbit(org, 2, org_size)), 0);
    BOOST_CHECK_EQUAL((arr_testbit(org, 3, org_size)), 1);
    BOOST_CHECK_EQUAL((arr_testbit(org, 4, org_size)), 0);
    BOOST_CHECK_EQUAL((arr_testbit(org, 5, org_size)), 0);
    BOOST_CHECK_EQUAL((arr_testbit(org, 6, org_size)), 1);
    BOOST_CHECK_EQUAL((arr_testbit(org, 7, org_size)), 1);
}

/* ----------------------------------------------- */
/* ---------test function int2buff---------------- */
/* ----------------------------------------------- */
BOOST_AUTO_TEST_CASE(test_int2buff_01) {
    int x = 0;
    char *b = int2buff(x, 2);

    BOOST_CHECK_EQUAL(b[0], 0);
    BOOST_CHECK_EQUAL(b[1], 0);
}


BOOST_AUTO_TEST_CASE(test_int2buff_02) {
    int x = 1227;
    char *b = int2buff(x, 2);

    BOOST_CHECK_EQUAL(b[1], 203);
    BOOST_CHECK_EQUAL(b[0], 4);
}

BOOST_AUTO_TEST_CASE(test_buff2int_01) {
    char b[2] = {4, 26};
    //int i = buff2int(b, 2);
    //BOOST_CHECK_EQUAL(i, );
    hex_print_buff(b, 2);
}

BOOST_AUTO_TEST_CASE(test_buff2int_02) {
    char b[3] = {0, 0, 0};
    int i = buff2int(b, 3);
    BOOST_CHECK_EQUAL(i, 0);
}

BOOST_AUTO_TEST_CASE(test_buff2int_03) {
    char b[2] = {5, 0};
    int i = buff2int(b, 2);
    //BOOST_CHECK_EQUAL(i, 122);
//    cout << i;
}

BOOST_AUTO_TEST_CASE(test_int2buff_03) {
    int x = 100;
    char *b = int2buff(x, 2);

    BOOST_CHECK_EQUAL(b[1], 100);
    BOOST_CHECK_EQUAL(b[0], 0);
}