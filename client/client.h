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
#include <climits>
#include <string>
#include <set>
#include <cerrno>

// unit = microsecond
#define DATA_INTERVAL 100000

/**
 * Read global title list from file.
 */
void read_gt_list(string filename, set<string> &gt_list);

/**
 * Read point code list from file.
 */
void read_pc_list(string filename, set<string> &pc_list);

/**
 * Read ssn list from file.
 */
void read_ssn_list(string filename, set<string> &ssn_list);

/**
 * Generate signal unit from set of ssn, pc, and gt.
 */
struct signal_unit generate_su(set<string> gt_set, set<string> ssn_set, set<string> pc_set);

/**
 * Random party address, value take from sets.
 */
void random_party_address(struct party_address &pa, set<string> gtt_set, set<string> pc_set, set<string> ssn_set);

/**
 * Random data 20 bytes.
 */
byte *random_data();

/**
 * Continuosly sent data.
 */
void loop_send();

/**
 * Create and connect socket. return fd of socket.
 */
int connect_sock();
 

/**
 * Sent data in file.
 */
void send_signal_in_file(const char *filename);

#endif