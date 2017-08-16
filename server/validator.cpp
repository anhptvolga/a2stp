/**
 * impl of validator
 */

#include "validator.h"

using namespace std;

extern gtt_table_type gtt_table;

int validate(signal_unit su, time_t time) {
    party_address calling = su.CgPA;
    party_address called = su.CdPA;
    // printsingal(su);
    if (!testbit(calling.indicator, BIT_G_POS)) {
        // routing on GT, check gt of CgPA and CdPA
        if (!memcmp(calling.gt, called.gt, GT_SIZE)) {
            write_vl_log(su, time, ERR_SAME_GT);
            return ERR_SAME_GT;
        }
        string gt = buffgt_to_str(called.gt);
        if (gtt_table.find(gt) == gtt_table.end()) {
            write_vl_log(su, time, ERR_NO_GT);
            return ERR_NO_GT;
        }
    } else {
        // routing on SSN, check DPC and SSN
        if (!memcmp(calling.pointCode, called.pointCode, PC_SIZE)) {
            write_vl_log(su, time, ERR_SAME_PC);
            return ERR_SAME_PC;
        }
    }
    return 0;
}

void write_vl_log(signal_unit su, time_t time, int errcode) {
    ofstream ofs(LFILE_DISCARD, std::ofstream::app);
    string gt;
    gt = buffgt_to_str(su.CgPA.gt);
    string stime(ctime(&time));
    byte* buff = su_to_buffer(su);
    ofs << stime.substr(0, stime.size()-1)
        << " Error code = " << errcode << " Signal: ";
    hex_print_buff(ofs, buff, SU_SIZE);
    ofs << endl;
    free(buff);
    ofs.close();
}
