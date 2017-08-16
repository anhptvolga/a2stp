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
	
	if (f.is_open()) {
		while (getline(f, line)) {
			size_t pos = line.find_first_of("#");
			size_t l = line.length();
			if (pos != -1) {
				line = line.erase(pos, l - pos);
			}

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
	//if (i1 != blist.end()) {
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

// main function for testing
// int main() {
// 	signal_unit s1 = new_su("0", "11111111111", "1003", "3", "11111111113", "1004", "2");
// 	signal_unit s2 = new_su("0", "11111111111", "2001", "3", "11111111113", "9999", "2");
// 	signal_unit s3 = new_su("0", "11111111111", "1993", "3", "11111111113", "1004", "2");
// 	signal_unit s4 = new_su("0", "11111111111", "2017", "3", "11111111113", "1004", "2");
// 	mapstrbool hmap;
// 	read_block_list(CFILE_SCREENING, hmap);
// 	check_block(s1, time(0), hmap);
// 	//print_su(s1);
// 	return 0;
// }