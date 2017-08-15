#ifndef __bitlib_h__
#define __bitlib_h__

#define CHAR_SIZE 8

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <string>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <sstream>
#include "../utils/su.h"

using namespace std;

/**
 * turn on i-th bit of num
 */
void onbit(char &num, int i);

/**
 * turn off i-th bit of num
 */
void offbit(char &num, int i);

/**
 * check i-th bit of num
 */
bool testbit(char num, int i);

/**
 * check i-th bit of buffer buff has buff_size bytes
 */
bool arr_testbit(const char *buff, int i, int buff_size);

/**
 * Turn on pos-th bit of buffer (buff), know size of buffer. 
 */
void arr_onbit(char *buff, int pos, int buff_size);

/**
 * Convert a unsigned short number to char *
 */
char *short2buff(unsigned short x);


/**
 * Convert a char * to unsigned short number
 */
unsigned short buff2short(char * b);
 

/**
 * Print signal unit as readable format
 */
void print_su(struct signal_unit su);

/**
 * Print all bit of byte c
 */
void bin_print_char(char c);

/**
 * Print all bits of buffer buff, know it size
 */
void bin_print_buff(const char *buff, int size);

/**
 * Print all bits of buffer buff, know it size
 */
void hex_print_buff(ostream os, const char *buff, int size);

#endif
