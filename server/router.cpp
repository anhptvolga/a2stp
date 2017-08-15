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

    filename = (pcode == STP_PC) ? LFILE_LOCAL : LFILE_FORWARD;

    ofs.open(filename, std::ofstream::app);
    ofs << stime.substr(0, stime.size()-1)
        << ": poitcode= " << pcode << " ssn= " << ssn;
    hex_print_buff(ofs, buff, SU_SIZE);
    ofs << endl;
    free(buff);
    ofs.close();
}
