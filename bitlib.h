#ifndef __bitlib_h__
#define __bitlib_h__

#define CHAR_SIZE 8

#include <cstdio>
#include <cstdlib>

/*
 * Print all bit of byte c
 */
void bin_print_char(char c) {
	for (int i = 0; i < CHAR_SIZE; i++) {
		if ((c & 0x80) != 0) {
			printf("1");
		} else {
			printf("0");
		}
		c = c << 1;
	}	
}

/*
 * Print all bits of buffer buff, know it size
 */
void bin_print_buff(const char *buff, int size) {
	for (int i = 0; i < size; i++) {
		bin_print_char(buff[i]);
		printf(" ");
	}
}

/**
 * turn on i-th bit of num
 */
void onbit(char &num, int i) {
    num |= 1 << i;
}

/**
 * turn off i-th bit of num
 */
void offbit(char &num, int i) {
    num &= ~(1 << i);
}

/**
 * check i-th bit of num
 */
bool testbit(char num, int i) {
    return (num & 1 << i) != 0;
}

/*
 * Turn on pos-th bit of buffer (buff), know size of buffer. 
 */
void arr_onbit(char *buff, int pos, int buff_size) {
	onbit(buff[buff_size - 1 - pos / CHAR_SIZE], pos % CHAR_SIZE);
}

/*
 * Store a number to buffer 
 */
char * int2buff(int i, int size) {
    char * buff = (char *)malloc(size);
	
	int bits = size * CHAR_SIZE;
	int n = bits;
    if(!buff) return NULL;

    // type punning because signed shift is implementation-defined
    unsigned u = *(unsigned *)&i;
    for(; bits--; u >>= 1)
        if (u & 1) 
			arr_onbit(buff, n - 1 - bits, size);

    return buff;
}

#endif
