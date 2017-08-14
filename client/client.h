#ifndef __client_h__
#define __client_h__

#include "utils/su.h"
#include "bitlib/bitlib.h"
#include "utils/const.h"
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>	
#include <fstream>
#include <iostream>
#include <string>
#include <set>
#include <errno.h>


char *pa_to_buffer(struct party_address p);
char *su_to_buffer(struct signal_unit s);
char *strgtt_to_buff(string strgtt);
void read_gtt_table(set<string> &gtt_set, set<string> &pc_set, set<string> &ssn_set);
char *random_data();
void random_party_address(struct party_address &pa, set<string> gtt_set, set<string> pc_set, set<string> ssn_set);
struct signal_unit generate_su();
void set_party_address(struct party_address &pa, string bitg, string gt, string pc, string ssn);
struct signal_unit generate_dum_su(const char *filename);

#endif
