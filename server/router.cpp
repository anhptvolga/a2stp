#include "router.h"

using namespace std;

extern gtt_table_type gtt_table;

void route_signal(signal_unit signal, time_t time) {
    std::ofstream ofs;
    const char* filename;
    std::string gt(signal.CgPA.gt, GT_SIZE);
    int pcode = 0;
    int ssn = 0;
    if (!testbit(signal.CgPA.indicator, BIT_G_POS)) {
        // routing on GT
        gtt_table_type::const_iterator tmp = gtt_table.find(signal.CdPA.gt);
        if (tmp != gtt_table.end()) {
            pcode = (tmp->second).first;
            ssn = (tmp->second).second;
        }
    } else {
        // routing on SSN
        pcode = buff2int(signal.CdPA.pointCode, 2);
        ssn = (int)signal.CdPA.subNumber;
    }

    filename = (pcode == STP_PC) ? LFILE_LOCAL : LFILE_FORWARD;

    ofs.open(filename, std::ofstream::app);
    ofs << ctime(&time) << ": poitcode= " << pcode << " ssn=" << ssn << endl;
    ofs.close();
}
