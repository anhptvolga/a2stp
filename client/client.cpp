#include "client.h"

using namespace std;

/**
 * Read global title list from file.
 */
void read_gt_list(string filename, set<string> &gt_list) {
    ifstream f(filename, ios::in);
    string line;
    gt_list.clear();
    if (f.is_open()) {
        while (!f.eof()) {
            f >> line;
            if (line.length() == 11) {
                gt_list.insert(line);
            }
        }
    } else
        cout << "unable to read file" << filename << endl;
    f.close();
}

/**
 * Read subsystem number from file.
 */
void read_ssn_list(string filename, set<string> &ssn_list) {
    ifstream f(filename, ios::in);
    string line;
    int x;
    ssn_list.clear();
    if (f.is_open()) {
        while (!f.eof()) {
            f >> line;
            x = atoi(line.c_str());
            if (x < 256) {
                ssn_list.insert(line);
            }
        }
    } else
        cout << "unable to read file" << filename << endl;
    f.close();
}

/**
 * Read point code number from file.
 */
void read_pc_list(string filename, set<string> &pc_list) {
    ifstream f(filename, ios::in);
    string line;
    int x;
    pc_list.clear();
    if (f.is_open()) {
        while (!f.eof()) {
            f >> line;
            x = atoi(line.c_str());
            if (x < 65536) {
                pc_list.insert(line);
            }
        }
    } else
        cout << "unable to read file" << filename << endl;
    f.close();
}


byte *random_data() {
	byte *d = new byte[MESSAGE_SIZE];
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
	memcpy(pa.pointCode, short2buff(pc), 2);

	// random subnumber
	it = ssn_set.begin();
	advance(it, rand() % ssn_set.size());
	int ssn = atoi((*it).c_str());
	pa.subNumber = ssn;

	// random global title
	it = gtt_set.begin();
	advance(it, rand() % gtt_set.size());
	memcpy(pa.gt, strgtt_to_buff(*it), 11);
}

/**
 * Generate signal unit from set of ssn, pc, and gt.
 */
struct signal_unit generate_su(set<string> gt_set, set<string> pc_set, set<string> ssn_set) {
	struct signal_unit su;
    random_party_address(su.CgPA, gt_set, pc_set, ssn_set);
    random_party_address(su.CdPA, gt_set, pc_set, ssn_set);
    memcpy(su.data, random_data(), MESSAGE_SIZE);
	return su;
}

#ifndef UNIT_TEST
// main loop. client will send data to server every 3s.
int main(int argc, char const *argv[]) {
    // test

    // cout << "Reading config file..." << endl;
    // set<string> lgt, lpc, lssn;
    // read_gt_list(LFILE_GT_LIST, lgt);
    // read_pc_list(LFILE_PC_LIST, lpc);
    // read_ssn_list(LFILE_SSN_LIST, lssn);

    // struct signal_unit su = generate_su(lgt, lpc, lssn);
    // //struct signal_unit su = generate_dum_su("dump/m1.txt");
    // byte *message = su_to_buffer(su);

    // // print some notification
    // cout << "Message: " << endl;
    // hex_print_buff(message, SU_SIZE);
    // cout << endl;

    // cout << "Original: " << endl;
    // print_su(su);
    // cout << endl;


    // main program 
    srand(time(NULL));
    
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

    cout << "Reading config file..." << endl;
    set<string> lgt, lpc, lssn;
    read_gt_list(LFILE_GT_LIST, lgt);
    read_pc_list(LFILE_PC_LIST, lpc);
    read_ssn_list(LFILE_SSN_LIST, lssn);

    if (!lgt.size() || !lpc.size() || !lssn.size()) {
        cout << "No invalid data in config file... Error" << endl;
        close(sock);
        exit(1);
    }

    while (true) {
        const byte *message = new byte[SU_SIZE];
        // generate data
        struct signal_unit su = generate_su(lgt, lpc, lssn);
        //struct signal_unit su = generate_dum_su("dump/m1.txt");
        message = su_to_buffer(su);

        // print some notification
        cout << "Message: " << endl;
        hex_print_buff(message, SU_SIZE);
        cout << endl;

        // send data to server
        ssize_t sent = send(sock, message, SU_SIZE, 0);
        if (sent < 0) {
            cout << "Send failed" << endl;
            close(sock);
            exit(1);
        } else {
            cout << sent << " bytes of message is sent!" << endl;
        }
        // sleep before send
        usleep(DATA_INTERVAL);
    }

    close(sock); // close socket
    return 0;
}

#endif
