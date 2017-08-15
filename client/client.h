#ifndef __client_h__
#define __client_h__

#include "../include/utils/su.h"
#include "../include/bitlib/bitlib.h"
#include "../include/utils/const.h"
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
#include <cerrno>

// 100ms
#define DATA_INTERVAL 100000

char *pa_to_buffer(struct party_address p);
char *su_to_buffer(struct signal_unit s);
char *strgtt_to_buff(string strgtt);

void read_gt_list(string filename, set<string> &gt_list);
void read_pc_list(string filename, set<string> &pc_list);
void read_ssn_list(string filename, set<string> &ssn_list);

struct signal_unit generate_su(set<string> gt_set, set<string> ssn_set, set<string> pc_set);
void random_party_address(struct party_address &pa, set<string> gtt_set, set<string> pc_set, set<string> ssn_set);
char *random_data();

void set_party_address(struct party_address &pa, string bitg, string gt, string pc, string ssn);
struct signal_unit generate_dum_su(const char *filename);

#endif