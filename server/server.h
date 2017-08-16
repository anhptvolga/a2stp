#ifndef __server_h__
#define __server_h__

#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <cstring>
#include <stdlib.h>
#include <unistd.h>

#include <poll.h>
#include <pthread.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "validator.h"
#include "screener.h"
#include "router.h"

#define MAX_CLIENTS 1024
#define QUEUE_LIMIT 5

#define MAX_CONN_TIME 4     // in seconds

typedef std::pair<byte*, time_t> raw_signal;
// typedef std::pair<int, int> pcssn;
// typedef std::unordered_map<char*, pcssn> gtt_table_type;

/**
 * read gtt table, config by user
 */
void read_gtt_table();

/**
 * receiver message from client
 */
void recv_message(void* ptr);

/**
 * handling message in queue
 */
void* proc_message(void* ptr);

/**
 * parsing party address from raw message
 */
void buff_to_pa(byte* raw, party_address & addr);

/**
 * parsing raw message to signal structure
 */
void trans_data(raw_signal raw, signal_unit &signal);

#endif
