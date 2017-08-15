#include "bitlib.h"

/**
 * Print all bit of byte c
 */
void bin_print_char(byte c) {
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
void bin_print_buff(const byte *buff, int size) {
	for (int i = 0; i < size; i++) {
		bin_print_char(buff[i]);
		cout << " ";
	}
}

/**
 * Print all bits of buffer buff, know it size
 */
void hex_print_buff(ofstream &os, const byte *buff, int size) {
	os << showbase << internal << setfill('0');
    for (int i = 0; i < size; i++) {
        os << hex << setw(4) << (unsigned int) buff[i] << " ";
    }
}

void hex_print_buff(const byte *buff, int size) {
	cout << showbase << internal << setfill('0');
    for (int i = 0; i < size; i++) {
        cout << hex << setw(4) << (unsigned int) buff[i] << " ";
    }
}

/**
 * turn on i-th bit of num
 */
void onbit(byte &num, int i) {
    num |= 1 << i;
}

/**
 * turn off i-th bit of num
 */
void offbit(byte &num, int i) {
    num &= ~(1 << i);
}

/**
 * check i-th bit of num
 */
bool testbit(byte num, int i) {
    return (num & 1 << i) != 0;
}

/**
 * check i-th bit of buffer buff has buff_size bytes
 */
bool arr_testbit(const byte *buff, int i, int buff_size) {
	return testbit(buff[i / CHAR_SIZE], i % CHAR_SIZE);
}

/*
 * Turn on pos-th bit of buffer (buff), know size of buffer. 
 */
void arr_onbit(byte *buff, int pos, int buff_size) {
	onbit(buff[pos / CHAR_SIZE], pos % CHAR_SIZE);
}


/**
 * Load a buffer to receive a number (GT number) 
 */
void print_su(struct signal_unit s) {
	cout << "DI: ";
	bin_print_char(s.CgPA.indicator);

	cout << endl << "DPC: " << dec << buff2short(s.CgPA.pointCode);
	cout << endl << "DSSN: " << (int)s.CgPA.subNumber;
	ostringstream convert;
	for (int i = 0; i < 11; i++) {
		convert << (int)s.CgPA.gt[i];	
	}
	cout << endl << "DGT: " << convert.str() << endl;

	cout << "SPC: " << buff2short(s.CdPA.pointCode) << endl;
	cout << "SSSN: " << (int)s.CdPA.subNumber << endl;
}

byte *short2buff(unsigned short x) {
	byte *b = new byte[2];
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
unsigned short buff2short(byte *b) {
	unsigned short x = 0;
	for (int i = 0; i < 16; ++i) {
		if (arr_testbit(b, i, 2))
			x += (1 << i);
	}
	return x;
}

/**
 * Concatenate all field of a party address as a array of octets
 */
 byte *pa_to_buffer(struct party_address p) {
	byte *ret = new byte[PA_SIZE];
	memset(ret, 0, PA_SIZE);	
	memcpy(ret, &p.indicator, 1);
	memcpy(ret + 1, p.pointCode, 2);
	memcpy(ret + 3, &p.subNumber, 1);
	memcpy(ret + 4, p.gt, 11);
	return ret;
}

/**
 * Concatenate all field of a signal unit as a array of octets
 */
byte *su_to_buffer(struct signal_unit s) {
	byte *pk = new byte[SU_SIZE];
	memset(pk, 0, SU_SIZE);			// set all bit to 0
	// from struct to bits
	const byte *cgpa_buf = pa_to_buffer(s.CgPA);
	const byte *cdpa_buf = pa_to_buffer(s.CdPA);
	// concat all to one 50 bytes buffer
	memcpy(pk, cgpa_buf, PA_SIZE);
	memcpy(pk + 15, cdpa_buf, PA_SIZE);	
	memcpy(pk + 30, s.data, MESSAGE_SIZE);
	return pk;
}

/*
 * Convert a global title (string) to array of octets
 */
 byte *strgtt_to_buff(string strgtt) {
	byte *buff = new byte[strgtt.length()];
	memset(buff, 0, strgtt.length());
	memcpy(buff, strgtt.c_str(), strgtt.length());
	for (unsigned int i = 0; i < strgtt.length(); ++i) {
		buff[i] -= '0';
	}
	return buff;
}

string buffgt_to_str(byte *gtt) {
    string res(11, 0);
    int i;
    for (i = 0; i < GT_SIZE; ++i) {
        res[i] = gtt[i];
    }
    return res;
}

void set_party_address(struct party_address &pa, string bitg, string gt, string pc, string ssn) {
	pa.indicator = 11;
	if (bitg == "1") {
		onbit(pa.indicator, 6);
	}
	int x = atoi(pc.c_str());
	memcpy(pa.pointCode, short2buff(x), 2);
	int y = atoi(ssn.c_str());
	pa.subNumber = y;
	memcpy(pa.gt, strgtt_to_buff(gt), 11);
}

struct signal_unit new_su(string sbitg, string sgt, string spc, string sssn, string dgt, string dpc, string dssn) {
	signal_unit su;
	set_party_address(su.CgPA, sbitg, sgt, spc, sssn);
	set_party_address(su.CdPA, "1", dgt, dpc, dssn);

	char data_dump[20] = "this is dummy data!";

	memcpy(su.data, data_dump, MESSAGE_SIZE);
	return su;
}

