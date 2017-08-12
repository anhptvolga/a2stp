/**
 * impl of validator
 */

#include "validator.h"

using namespace std;

int validate(signal_unit su, time_t time) {
    //cout << "indicator: "; bin_print_char(su.CgPA.indicator); cout << endl;
    //cout << "PC: "; bin_print_buff(su.CgPA.pointCode, 2); cout << endl;
    //cout << "ssn: "; bin_print_char(su.CgPA.subNumber); cout << endl;
    //cout << "gt: "; bin_print_buff(su.CgPA.gt, 11); cout << endl;

    party_address calling = su.CgPA;
    party_address called = su.CdPA;
    if (!testbit(calling.indicator, BIT_G_POS)) {
        // routing on GT, check gt of CgPA and CdPA
        if (!memcmp(calling.gt, called.gt, GT_SIZE)) {
            write_vl_log(su, time, ERR_SAME_GT);
        }
    } else {
        // routing on SSN, check DPC and SSN
        if (!memcmp(calling.pointCode, called.pointCode, PC_SIZE)) {
            write_vl_log(su, time, ERR_SAME_PC);
        }
    }
    return 0;
}

void write_vl_log(signal_unit su, time_t time, int errcode) {
    ofstream ofs(LFILE_DISCARD, std::ofstream::app);
    cout << ctime(&time) << " : "
         << su.CgPA.gt << " : "
         << errcode << endl;
    ofs.close();
}
