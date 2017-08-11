#ifndef __su_h__
#define __su_h__

struct party_address {
	char indicator;
	char pointCode[2];
	char subNumber;
	char gt[11];
};

struct signal_unit {
	struct party_address CgPA;
	struct party_address CdPA;

	char data[20];
};

#endif
