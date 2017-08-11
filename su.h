#ifndef __su_h__
#define __su_h__

#define SU_SIZE 50
#define PA_SIZE 15
#define DATA_SIZE 20
#include <cstdlib>
#include <cstring>


// party address for calling and called
// total size of pa = 15 bytes
struct party_address {
	char indicator;			
	char pointCode[2];		
	char subNumber;
	char gt[11];
};

// signal unit - a package of data from client to server
// total size = 50 bytes
struct signal_unit {
	struct party_address CgPA;
	struct party_address CdPA;

	char data[20];
};

// connect all party_address
const char *pa_to_buffer(struct party_address p) {
	char *ret = (char *)malloc(PA_SIZE * sizeof(char));
	memcpy(ret, &p.indicator, 1);
	memcpy(ret + 2, p.pointCode, 2);
	memcpy(ret + 3, &p.subNumber, 1);
	memcpy(ret + 5, p.gt, 11);	
	return ret;
}

// function transform signal_unit to buffer -> transfer throught socket
const char *su_to_buffer(struct signal_unit s) {
	char *pk = (char *)malloc(SU_SIZE * sizeof(char));
	const char *cgpa_buf = pa_to_buffer(s.CgPA);
	const char *cdpa_buf = pa_to_buffer(s.CdPA);
	memcpy(pk, cgpa_buf, PA_SIZE);
	memcpy(pk + 15, cdpa_buf, PA_SIZE);	
	memcpy(pk + 30, s.data, DATA_SIZE);
	return pk;
}

#endif
