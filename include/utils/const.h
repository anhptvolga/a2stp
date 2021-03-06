#ifndef __const_h__
#define __const_h__

/* server address */
// #define SV_IP "192.168.2.126"
#define SV_IP "192.168.2.72"
// #define SV_IP "127.0.0.1"
#define SV_PORT 54321

/* stp config */
#define STP_PC 1000
#define STP_SSN 6

/* config filenames */
#define CFILE_SCREENING "screening.conf"
#define CFILE_GTT       "gtt.conf"

/* output filenames */
#define LFILE_BLOCK     "block.log"
#define LFILE_DISCARD   "discard.log"
#define LFILE_LOCAL     "local.log"
#define LFILE_FORWARD   "forward.log"

/* client config file */
#define LFILE_PC_LIST "pc.list"
#define LFILE_GT_LIST "gt.list"
#define LFILE_SSN_LIST "ssn.list"

#endif
