#ifndef __validator_h__
#define __validator_h__

#include "../su.h"

/* list of error codes */
#define ERR_SAME_SD 1
#define ERR_STP_SSN 2

/**
 * validate signal unit
 * return 0 if ok or error code
 */
int validate(signal_unit su);

/**
 * write validating log with error code 
 */
void writeVlLog(signal_unit su, int errcode);

#endif
