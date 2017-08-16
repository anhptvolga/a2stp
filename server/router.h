#ifndef __router_h__
#define __router_h__

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <utility>
#include "bitlib/bitlib.h"
#include "utils/su.h"
#include "utils/const.h"
#include "validator.h"

void route_signal(signal_unit signal, time_t time);

#endif
