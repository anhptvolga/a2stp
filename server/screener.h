#ifndef __screener_h__
#define __screener_h__

#include "../su.h"
#include "../bitlib.h"
#include "../const.h"
#include <fstream>
#include <iostream>
#include <string>
#include <cstring>
#include <unordered_map>
#include <ctime>


typedef std::unordered_map<std::string, bool> mapstrbool;
typedef std::unordered_map<std::string, bool>::iterator iterstrbool;

string h(int spc, int dpc);
void read_block_list(const char *filename, mapstrbool &blist);
bool check_block(struct signal_unit su, time_t t, mapstrbool blist);

#endif
