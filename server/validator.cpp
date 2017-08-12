/**
 * impl of validator
 */

#include "validator.h"

using namespace std;

void printpa(party_address pa) {
    cout << "indicator: "; bin_print_char(pa.indicator); cout << endl;
    cout << "PC: " << buff2int(pa.pointCode, 2); cout << " "; bin_print_buff(pa.pointCode, 2);
    cout << endl;
    cout << "ssn: " << (char)(pa.subNumber+48) << endl;
    cout << "gt: "; bin_print_buff(pa.gt, 11); cout << endl;
}
void printsingal(signal_unit su) {
    cout << "CgPA: " << endl;
    printpa(su.CgPA);
    cout << "CdPA: " << endl;
    printpa(su.CdPA);
}

int validate(signal_unit su, time_t time) {
    party_address calling = su.CgPA;
    party_address called = su.CdPA;
    printsingal(su);
    if (!testbit(calling.indicator, BIT_G_POS)) {
        // routing on GT, check gt of CgPA and CdPA
        if (!memcmp(calling.gt, called.gt, GT_SIZE)) {
            write_vl_log(su, time, ERR_SAME_GT);
            return ERR_SAME_GT;
        }
    } else {
        // routing on SSN, check DPC and SSN
        if (!memcmp(calling.pointCode, called.pointCode, PC_SIZE)) {
            write_vl_log(su, time, ERR_SAME_PC);
            return ERR_SAME_PC;
        }
        // point code equals stp but ssn dif
        if (STP_PC == buff2int(called.pointCode, PC_SIZE) &&
                STP_SSN != called.subNumber) {
            write_vl_log(su, time, ERR_STP_SSN);
            return ERR_STP_SSN;
        }
    }
    return 0;
}

void write_vl_log(signal_unit su, time_t time, int errcode) {
    ofstream ofs(LFILE_DISCARD, std::ofstream::app);
    string gt(su.CgPA.gt, GT_SIZE);
    ofs << ctime(&time) << ": "
         << "pointcode = " << buff2int(su.CdPA.pointCode, PC_SIZE) << " : "
         << errcode << endl;
    ofs.close();
}
