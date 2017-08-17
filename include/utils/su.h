#ifndef __su_h__
#define __su_h__

#include <string>
#include <utility>
#include <unordered_map>

#define INDICATOR_SIZE 1
#define SU_SIZE 50
#define PA_SIZE 15
#define GT_SIZE 11
#define PC_SIZE 2
#define SSN_SIZE 1
#define BYTE_SIZE 8
#define BIT_G_POS 6
#define MESSAGE_SIZE 20

typedef unsigned char byte;

// party address for calling and called
// total size of pa = 15 bytes
struct party_address {
	byte indicator;					// 1 byte
	byte pointCode[PC_SIZE]; 		// 2 bytes
	byte subNumber;					// 1 byte
	byte gt[GT_SIZE];				// 11 byte
};

// signal unit - a package of data from client to server
// total size = 50 bytes
struct signal_unit {
	struct party_address CgPA;
	struct party_address CdPA;
	byte data[MESSAGE_SIZE];
};

typedef std::pair<int, int> pcssn;
typedef std::unordered_map<std::string, pcssn> gtt_table_type;

#endif
