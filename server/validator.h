#ifndef __validator_h__
#define __validator_h__

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include "../include/utils/su.h"
#include "../include/utils/const.h"
#include "../include/bitlib/bitlib.h"

/* list of error codes */
#define ERR_SAME_PC 1   // SPC == DPC
#define ERR_SAME_GT 2   // SGT == DGT
#define ERR_STP_SSN 3   // invalid subsystem number of STP
#define ERR_NO_GT 4     // GTT not exist

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
