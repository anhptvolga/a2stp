#include "bitlib.h"

/**
 * Print all bit of byte c
 */
void bin_print_char(char c) {
	for (int i = 0; i < CHAR_SIZE; i++) {
		if (testbit(c, i))
			cout << "1";
		else
			cout << "0";
	}
}

/**
 * Print all bits of buffer buff, know it size
 */
void bin_print_buff(const char *buff, int size) {
	for (int i = 0; i < size; i++) {
		bin_print_char(buff[i]);
		cout << " ";
	}
}

/**
 * Print all bits of buffer buff, know it size
 */
void hex_print_buff(const char *buff, int size) {
	cout << showbase << internal << setfill('0');
    for (int i = 0; i < size; i++) {
        cout << hex << setw(4) << (unsigned int) buff[i] << " ";
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
	return testbit(buff[i / CHAR_SIZE], i % CHAR_SIZE);
}

/*
 * Turn on pos-th bit of buffer (buff), know size of buffer. 
 */
void arr_onbit(char *buff, int pos, int buff_size) {
	onbit(buff[pos / CHAR_SIZE], pos % CHAR_SIZE);
}


/**
 * Load a buffer to receive a number (GT number) 
 */
void print_su(struct signal_unit s) {
	cout << "DI: ";
	bin_print_char(s.CgPA.indicator);

	cout << endl << "DPC: " << dec << s.CgPA.pointCode;
	cout << endl << "DSSN: " << (int)s.CgPA.subNumber;
	ostringstream convert;
	for (int i = 0; i < 11; i++) {
		convert << (int)s.CgPA.gt[i];	
	}
	cout << endl << "DGT: " << convert.str() << endl;

	cout << "SPC: " << s.CdPA.pointCode << endl;
	cout << "SSSN: " << (int)s.CdPA.subNumber << endl;
}

char *short2buff(unsigned short x) {
	char *b = new char[2];
	memset(b, 0, 2);
	for (int i = 0; i < 16; ++i) {
		if ((x & 1 << i) != 0) {
			arr_onbit(b, i, 2);
		} 
	}

	return b;
}

/**
 * Convert a char * to unsigned short number
 */
unsigned short buff2short(char *b) {
	unsigned short x = 0;
	for (int i = 0; i < 16; ++i) {
		if (arr_testbit(b, i, 2))
			x += (1 << i);
	}
	return x;
}
 