#include "bitlib.h"
#include "../utils/su.h"

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

/**
 * check i-th bit of buffer buff has buff_size bytes
 */
bool arr_testbit(const char *buff, int i, int buff_size) {
	return testbit(buff[buff_size - 1 - i / CHAR_SIZE], i % CHAR_SIZE);
}

/*
 * Turn on pos-th bit of buffer (buff), know size of buffer. 
 */
void arr_onbit(char *buff, int pos, int buff_size) {
	onbit(buff[buff_size - 1 - pos / CHAR_SIZE], pos % CHAR_SIZE);
}

/*
 * Store a number to buffer (GT number)
 */
char * int2buff(int numb, int size) {
    char *buff = new char[size];
	memset(buff, 0, size);

	int bits = size * CHAR_SIZE;
	int n = bits;
    if(!buff) return NULL;

    // type punning because signed shift is implementation-defined
    unsigned u = *(unsigned *)&numb;
    for(; bits--; u >>= 1)
        if (u & 1) 
			arr_onbit(buff, n - 1 - bits, size);

    return buff;
}

/*
 * Load a buffer to receive a number (GT number) 
 */
int buff2int(const char *buff, int buff_size) {
	int ret = 0;
	int bits = buff_size * CHAR_SIZE;
	for (int i = bits - 1; i >= 0; --i) {
		ret += (1 << i) * arr_testbit(buff, i, buff_size);
	}
	return ret;
}


/*
 * Load a buffer to receive a number (GT number) 
 */
void print_su(struct signal_unit s) {
	cout << "SU: " << endl;
	cout << "DI: ";
	bin_print_char(s.CgPA.indicator);

	int x = buff2int(s.CgPA.pointCode, 2);
	cout << endl << "DPC: " << x;
	cout << endl << "DSSN: " << (int)s.CgPA.subNumber;
	ostringstream convert;
	for (int i = 0; i < 11; i++) {
		convert << (int)s.CgPA.gt[i];	
	}
	cout << endl << "DGT: " << convert.str() << endl;

	x = buff2int(s.CdPA.pointCode, 2);
	cout << "SPC: " << x << endl;
	cout << "SSSN: " << (int)s.CdPA.subNumber << endl;
}


