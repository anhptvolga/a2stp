#include "screener.h"

string h(byte spc[2], byte dpc[2]) {
	int x = buff2short(spc);
	int y = buff2short(dpc);

	ostringstream convert;
	convert << x;
	convert << y;

	return convert.str();
}

void read_block_list(const char *filename, mapstrbool &blist) {	
	blist.clear();
	string bspc, bdpc, h;
	string line;
	ifstream f(filename);
        
        // checking file open
	if (f.is_open()) {
		while (getline(f, line)) {
                        // delete comment
			size_t pos = line.find_first_of("#");
			size_t l = line.length();
			if (pos != string::npos) {
				line = line.erase(pos, l - pos);
			}

                        // process
			istringstream iss(line);
			if (!(iss >> bspc >> bdpc)) { continue; }
			h = bspc + bdpc;
			blist[h] = true;
		}
	}
	
	f.close();
}

bool check_block(struct signal_unit su, time_t t, mapstrbool blist) {
	// key to check s -> d
	string key = h(su.CgPA.pointCode, su.CdPA.pointCode);
	ostringstream sconvert;
	sconvert << buff2short(su.CgPA.pointCode);
	string spc = sconvert.str();

	ostringstream dconvert;
	dconvert << buff2short(su.CdPA.pointCode);
	string dpc = dconvert.str();
	
	// key to check s -> *
	string g_key = spc + "*";
	// key to check * -> d
	string d_key = "*" + dpc;
	// key to check all
	string a_key = "**";

	iterstrbool i1 = blist.find(key);
	iterstrbool i2 = blist.find(g_key);
	iterstrbool i3 = blist.find(d_key);
	iterstrbool i4 = blist.find(a_key);
	
	// found the key in map -> block it -> return false
	if (i1 != blist.end() || i2 != blist.end() || i3 != blist.end() || i4 != blist.end()) {
                // write block log file
		ofstream ofs(LFILE_BLOCK, ofstream::out | ofstream::app);
		if (ofs.is_open()) {
			string stime(ctime(&t));
			byte* buff = su_to_buffer(su);
			ofs << stime.substr(0, stime.size()-1)
				<< " Signal: ";
			hex_print_buff(ofs, buff, SU_SIZE);
			ofs << endl;
			free(buff);
			ofs.close();

		}
		ofs.close();
		return false;
	} 
    return true;
}

