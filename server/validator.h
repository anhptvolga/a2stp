#ifndef __validator_h__
#define __validator_h__

#include <iostream>
#include <cstring>
#include <fstream>
#include "../su.h"
#include "../const.h"
#include "../bitlib.h"

/* list of error codes */
#define ERR_SAME_PC 1
#define ERR_SAME_GT 2
#define ERR_STP_SSN 3

/**
 * validate signal unit
 * return 0 if ok or error code
 */
int validate(signal_unit su, time_t time);

/**
 * write validating log with error code 
 */
void write_vl_log(signal_unit su, time_t time, int errcode);

#endif
