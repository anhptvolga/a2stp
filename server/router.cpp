#include "router.h"

using namespace std;

extern gtt_table_type gtt_table;

void route_signal(signal_unit signal, time_t time) {
    std::ofstream ofs;
    const char* filename;
    std::string gt = buffgt_to_str(signal.CgPA.gt);
    string stime(ctime(&time));
    byte* buff = su_to_buffer(signal);
    unsigned short pcode = 0;
    byte ssn = 0;
    bool is_ssn_dif = false;
    if (!testbit(signal.CgPA.indicator, BIT_G_POS)) {
        // routing on GT
        string gtt = buffgt_to_str(signal.CdPA.gt);
        gtt_table_type::const_iterator tmp = gtt_table.find(gtt);
        if (tmp != gtt_table.end()) {
            pcode = (unsigned short)(tmp->second).first;
            ssn = (byte)(tmp->second).second;
        }
    } else {
        // routing on SSN
        pcode = buff2short(signal.CdPA.pointCode);
        ssn = signal.CdPA.subNumber;
    }

    // check: is message for stp server
    if (pcode == STP_PC) {
        if (ssn != STP_SSN) {
            filename = LFILE_DISCARD;
            is_ssn_dif = true;
        } else {
            filename = LFILE_LOCAL;
        }
    } else {
        filename = LFILE_FORWARD;
    }
    ofs.open(filename, std::ofstream::app);
    // check file
    if (!ofs.is_open()) {
        std::cout << "can not open file for routing" << std::endl;
    } else {
        ofs << stime.substr(0, stime.size()-1) << " ";
        if (is_ssn_dif) {
            ofs << "Error code = " << ERR_STP_SSN << " Signal: ";
        }
        hex_print_buff(ofs, buff, SU_SIZE);
        ofs << endl;
        ofs.close(); 
    }
    free(buff);
}
