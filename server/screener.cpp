#include "screener.h"

string h(char spc[2], char dpc[2]) {
	int x = buff2int(spc, 2);
	int y = buff2int(dpc, 2);

	ostringstream convert;
	convert << x;
	convert << y;

	return convert.str();
}

void read_block_list(const char *filename, mapstrbool &blist) {	
	blist.clear();
	string bspc, bdpc, h;

	ifstream f(filename, ios::in);
	
	if (f.is_open()) {
		while (!f.eof()) {
			f >> bspc >> bdpc;
			h = bspc + bdpc;
			blist[h] = true;
		}
	}
	
	f.close();
}

bool check_block(struct signal_unit su, time_t t, mapstrbool blist) {
	// key to check s -> d
	string key = h(su.CgPA.pointCode, su.CdPA.pointCode);
	// key to check s -> *
	string g_key = h(su.CgPA.pointCode, 0);
	// key to check * -> d
	string d_key = h(0, su.CdPA.pointCode);

	iterstrbool i1 = blist.find(key);
	iterstrbool i2 = blist.find(g_key);
	iterstrbool i3 = blist.find(d_key);
	
	if (i1 == blist.end() && i2 == blist.end() && i3 == blist.end()) {
		ofstream f(LFILE_BLOCK, ios::out);
		if (f.is_open()) {
			f << ctime(&t) 	<< " " << buff2int(su.CgPA.pointCode, 2) 
							<< " " << buff2int(su.CgPA.pointCode, 2) 
							<< std::endl;
		}
		f.close();
	} 
}
