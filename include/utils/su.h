#ifndef __su_h__
#define __su_h__

#include <string>
#include <utility>
#include <unordered_map>

#define SU_SIZE 50
#define PA_SIZE 15
#define GT_SIZE 11
#define PC_SIZE 2
#define BIT_G_POS 6
#define MESSAGE_SIZE 20


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

typedef std::pair<int, int> pcssn;
typedef std::unordered_map<std::string, pcssn> gtt_table_type;

#endif
