#include "client.h"

using namespace std;

/*
 * Concatenate all field of a party address as a array of octets
 */
char *pa_to_buffer(struct party_address p) {
	char *ret = new char[PA_SIZE];
	memset(ret, 0, PA_SIZE);
	memcpy(ret, &p.indicator, 1);
	memcpy(ret + 1, p.pointCode, 2);
	memcpy(ret + 3, &p.subNumber, 1);
	memcpy(ret + 4, p.gt, 11);
	return ret;
}

/*
 * Concatenate all field of a signal unit as a array of octets
 */
char *su_to_buffer(struct signal_unit s) {
	char *pk = new char[SU_SIZE];
	memset(pk, 0, SU_SIZE);
	const char *cgpa_buf = pa_to_buffer(s.CgPA);
	const char *cdpa_buf = pa_to_buffer(s.CdPA);
	memcpy(pk, cgpa_buf, PA_SIZE);
	memcpy(pk + 15, cdpa_buf, PA_SIZE);	
	memcpy(pk + 30, s.data, MESSAGE_SIZE);
	return pk;
}


/*
 * Convert a global title (string) to array of octets
 */
char *strgtt_to_buff(string strgtt) {
	char *buff = new char[strgtt.length()];
	memset(buff, 0, strgtt.length());
	memcpy(buff, strgtt.c_str(), strgtt.length());
	for (int i = 0; i < strgtt.length(); ++i) {
		buff[i] -= '0';
	}
	return buff;
}

/*
 * Read GTT table and collect all values of global title, pointcode and subsystem number.
 */
void read_gtt_table(set<string> &gtt_set, set<string> &pc_set, set<string> &ssn_set) {
	string line;
	string gt, pc, ssn;

	ifstream f(CFILE_GTT, ios::in);
	if (f.is_open()) {
		while (!f.eof()) {
			f >> gt >> pc >> ssn;
			gtt_set.insert(gt);
			pc_set.insert(pc);
			ssn_set.insert(ssn);
		}
	}
	f.close();
}

char *random_data() {
	char *d = new char[MESSAGE_SIZE];
	memset(d, 0, MESSAGE_SIZE);
	d[MESSAGE_SIZE - 1] = 0;
	for (int i = 0; i < MESSAGE_SIZE - 1; i++) {
		d[i] = rand() % 27 + 97;
	}
	return d;
}

void random_party_address(struct party_address &pa, set<string> gtt_set, set<string> pc_set, set<string> ssn_set) {
	// indicator
	pa.indicator = 11;
	// random bit G
	if ((rand() % 10 + 1) % 2) {
		onbit(pa.indicator, 6);
	}
	 
	set<string>::iterator it;

	// random point code
	it = pc_set.begin();
	advance(it, rand() % pc_set.size());
	int pc = atoi((*it).c_str());
	memcpy(pa.pointCode, int2buff(pc, 2), 2);

	// random subnumber 1-6
	it = ssn_set.begin();
	advance(it, rand() % ssn_set.size());
	int ssn = atoi((*it).c_str());
	pa.subNumber = ssn;

	// random global title
	it = gtt_set.begin();
	advance(it, rand() % gtt_set.size());
	memcpy(pa.gt, strgtt_to_buff(*it), 11);
}

// Randomly generate signal unit.
// Structure
// INDICATOR 8 bits - random bit G - bit 6
// Point code 2 bytes - take random from config file
// Subsystem number 4 bytes - take random from config file
// Global title 11 bytes - take random from config file
// Data - 20 bytes random
struct signal_unit generate_su() {
	struct signal_unit su;
	set<string> gtt_set, ssn_set, pc_set;
	
	read_gtt_table(gtt_set, pc_set, ssn_set);
	random_party_address(su.CgPA, gtt_set, pc_set, ssn_set);
	random_party_address(su.CdPA, gtt_set, pc_set, ssn_set);
	strcpy(su.data, random_data());
	return su;
}

void set_party_address(struct party_address &pa, string bitg, string gt, string pc, string ssn) {
	pa.indicator = 11;
	if (bitg == "1") {
		onbit(pa.indicator, 6);
	}
	int x = atoi(pc.c_str());
	memcpy(pa.pointCode, int2buff(x, 2), 2);
	int y = atoi(ssn.c_str());
	pa.subNumber = y;
	memcpy(pa.gt, strgtt_to_buff(gt), 11);
}

struct signal_unit generate_dum_su(const char *filename) {
	signal_unit su;
	
	ifstream f(filename, ios::in);
	string sbitg, sgt, spc, sssn, dgt, dpc, dssn;
	if (f.is_open()) {
		f >> sbitg;
		f >> sgt >> spc >> sssn;
		f >> dgt >> dpc >> dssn;
	} else {
		cout << "Unable to open file" << endl;	
	}
	f.close();

	set_party_address(su.CgPA, sbitg, sgt, spc, sssn);
	set_party_address(su.CdPA, "1", dgt, dpc, dssn);
	strcpy(su.data, random_data());
	return su;	
}

// main loop. client will send data to server every 3s.
int main(int argc, char const *argv[]) {

	srand(time(NULL));
	
	//while (1) {
		// Connect to socket
		int sock;
		struct sockaddr_in server;

		// Create socket
		sock = socket(AF_INET, SOCK_STREAM, 0);
		if (sock < 0) {
			cout << "Could not create socket" << endl;
			exit(1);
		}
		cout << "Socket created" << endl;

		// Config
		server.sin_addr.s_addr = inet_addr(SV_IP);
		server.sin_family = AF_INET;
		server.sin_port = htons(SV_PORT);
	
		// Connect to server
		if (connect(sock, (struct sockaddr*)&server, sizeof(server)) == -1) {
			cout << "Connect failed. Error " << strerror(errno) << endl;
			exit(1);
		}	

		cout << "Connected" << endl;
	
		const char *message = new char[SU_SIZE];
		
		// generate data

		//struct signal_unit su = generate_data();
		struct signal_unit su = generate_dum_su("dump/m1.txt");

		message = su_to_buffer(su);
		//cout << "message: " << endl;
		bin_print_buff(message, SU_SIZE);
		//print_su(su);
		//cout << endl;
		// send data
		if (send(sock, message, SU_SIZE, 0) < 0) {	
			cout << "Send failed" << endl;
			exit(1);
		} else {
			cout << "message is sent!" << endl;
		}

		close(sock);
		//sleep(3);
	//}

	return 0;
}
