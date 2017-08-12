#ifndef __bitlib_h__
#define __bitlib_h__

#define CHAR_SIZE 8

#include <cstdio>
#include <cstdlib>
#include <cmath>

/*
 * Print all bit of byte c
 */
void bin_print_char(char c);

/*
 * Print all bits of buffer buff, know it size
 */
void bin_print_buff(const char *buff, int size);

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

/*
 * Turn on pos-th bit of buffer (buff), know size of buffer. 
 */
void arr_onbit(char *buff, int pos, int buff_size);

/*
 * Store a number to buffer (GT number)
 */
char * int2buff(int i, int size);

/*
 * Load a buffer to receive a number (GT number) 
 */
int buff2int(const char *buff, int buff_size);

#endif
