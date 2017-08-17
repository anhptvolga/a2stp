#ifndef __screener_h__
#define __screener_h__

#include "../include/utils/su.h"
#include "../include/bitlib/bitlib.h"
#include "../include/utils/const.h"
#include <fstream>
#include <iostream>
#include <string>
#include <cstring>
#include <unordered_map>
#include <ctime>

typedef std::unordered_map<std::string, bool> mapstrbool;
typedef std::unordered_map<std::string, bool>::iterator iterstrbool;

/**
 * hash function: return hash value of 2 subsystem number
 */
string h(int spc, int dpc);

/**
 * read user's blocking list config
 */
void read_block_list(const char *filename, mapstrbool &blist);

/**
 * check is signal blocked by user's config
 * return false if signal's blocked and true if signal's non-blocked
 */
bool check_block(struct signal_unit su, time_t t, mapstrbool blist);

#endif
