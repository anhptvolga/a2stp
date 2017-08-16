/**
 * stp server
 */

#include "server.h"

using namespace std;

/****/
// queue< pair<signal_unit, time_t> > qsignals;
queue< pair<byte*, time_t> > qsignals;
pthread_mutex_t qsmutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t qcond = PTHREAD_COND_INITIALIZER;
gtt_table_type gtt_table;
mapstrbool blockmap;

int main(int argc, char* argv[]) {
    pthread_t processer;

    // read config file
    read_gtt_table();
    read_block_list(CFILE_SCREENING, blockmap);

    // pthread_create(&recver, NULL, &recv_signal, NULL);
    pthread_create(&processer, NULL, &proc_signal, NULL);

    // pthread_join(recver, NULL);
    // pthread_join(processer, NULL);

    recv_signal(NULL);

    return 0;
}

void recv_signal(void* ptr) {
    int socketid;           // server socket
    int socketcl;           // client socket
    int status;
    int count, i;
    byte buff[SU_SIZE];
    byte* data;
    sockaddr_in socketaddr;
    sockaddr claddr;        // client address
    socklen_t claddrlen;
    // Poll
    pollfd clients[MAX_CLIENTS];
    clock_t lastconn[MAX_CLIENTS];
    int maxi = 0, nready = 0;
    time_t curtime;

    std::cout << "starting server" << std::endl;
    // create
    socketid = socket(AF_INET, SOCK_STREAM, 0);
    if (socketid < 0) {
        std::cout << "create socket fail" << std::endl;
    }
    // bind
    socketaddr.sin_family = AF_INET;
    socketaddr.sin_port = htons(SV_PORT);
    socketaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    status = bind(socketid, (sockaddr*) &socketaddr, sizeof(socketaddr));
    if (status == -1) {
        // error
        cout << "error in binding" << endl;
        exit(1);
    }

    // listen
    status = listen(socketid, QUEUE_LIMIT);
    if (status == -1) {
        cout << "error in listening" << endl;
        exit(1);
    }
    cout << "listening" << endl;
    // init poll
    for (i = 1; i < MAX_CLIENTS; ++i) clients[i].fd = -1;
    clients[0].fd = socketid;
    clients[0].events = POLLIN;//POLLRDNORM;
    maxi = 0;
    while (1) {
        // get number of ready clients
        nready = poll(clients, maxi+1, -1);
        // client[0]: accept new client
        if (clients[0].revents & POLLIN) {
            cout << "wait" << endl;
            socketcl = accept(socketid, (sockaddr*) &claddr, &claddrlen);
            cout << "--" << endl;
            if (socketcl == -1) {
                cout << "error in accepting" << endl;
                exit(1);
            }
            // add new client to poll
            for (i = 1; i < MAX_CLIENTS; ++i)
                if (clients[i].fd < 0) { 
                    clients[i].fd = socketcl;
                    clients[i].events = POLLIN;
                    lastconn[i] = clock();
                    cout << "add new client to poll" << endl;
                    break;
                }
            // check if number of clients > max_clients
            if (i == MAX_CLIENTS) {
                cout << "clients max" << endl;
                exit(1);
            }
            clients[i].revents = POLLRDNORM;
            if (i > maxi) maxi = i;
        }
        // check all clients
        for (i = 1; i < MAX_CLIENTS; ++i) {
            if (clients[i].revents < 0) continue;
            // ready for reading and no error
            if (clients[i].revents == POLLIN && clients[i].revents != POLLERR) {
                count = recv(socketcl, (void*)buff, SU_SIZE, 0);
                if (count <= 0) {
                    // exit(1);
                } else {
                    // push signal to queue
                    time(&curtime);
                    data = (byte*) malloc(SU_SIZE);
                    memcpy(data, buff, SU_SIZE);

                    pthread_mutex_lock(&qsmutex);
                    qsignals.push(make_pair(data, curtime));
                    cout << "recv: " << i << " " << count << "ok. push to queue. size = " << qsignals.size() << endl;
                    pthread_mutex_unlock(&qsmutex);
                    pthread_cond_signal(&qcond);
                    hex_print_buff(qsignals.front().first, SU_SIZE);
                    cout << endl;
                    // save time
                    lastconn[i] = clock();
                }
            }
            // free space in poll and close socket
            if ((clock() - lastconn[i])/CLOCKS_PER_SEC > MAX_CONN_TIME) {
                cout << "close connect " << i << endl;
                clients[i].fd = -1;
                close(socketcl);
            }
            if (--nready <= 0) break;   // out if nomore ready client
        }
    }
    close(socketid);
    // return NULL;
}

void* proc_signal(void* ptr) {
    raw_signal cur;
    signal_unit su;
    while (1) {
        pthread_mutex_lock(&qsmutex);
        if (qsignals.empty()) {
            pthread_cond_wait(&qcond, &qsmutex);
        }
        // get signal in queue
        cur = qsignals.front();
        qsignals.pop();
        pthread_mutex_unlock(&qsmutex);
        // process
        cout << " process - ";
        hex_print_buff(cur.first, SU_SIZE);
        trans_data(cur, su);
        cout << endl;
        hex_print_buff(su.data, 20);
        cout << endl;
        if (check_block(su, cur.second, blockmap) && !validate(su, cur.second)) {
            route_signal(su, cur.second);
        }
        free(cur.first);
    }
    return NULL;
}

void buff_to_pa(byte* raw, party_address &addr) {
    addr.indicator = raw[0];
    memcpy(addr.pointCode, raw+1, 2);
    addr.subNumber = raw[3];
    memcpy(addr.gt, raw+4, 11);
}

void trans_data(raw_signal raw, signal_unit &signal) {
    buff_to_pa(raw.first, signal.CgPA);
    buff_to_pa(raw.first+15, signal.CdPA);
    memcpy(signal.data, raw.first+30, 20);
}

void read_gtt_table() {
    ifstream ifs(CFILE_GTT);
    string gt, tmp;
    string::size_type sz;
    int pcode, ssn;
    unsigned int i;
    if (!ifs.is_open()) {
        cout << "err: cannot read gtt config file" << endl;
        exit(1);
    }

    while (!ifs.eof()) {
        getline(ifs, tmp);
        // std::cout << tmp << std::endl;
        if (tmp[0] != '#' && tmp.size() != 0) {
            gt = tmp.substr(0, 11);
            // std::cout << tmp.size() << std::endl;
            // std::cout << "|" << tmp.substr(12,4) << "|" << std::endl;
            // std::cout << tmp.substr(14,1) << std::endl;

            sscanf(tmp.substr(12).c_str(), "%i %i", &pcode, &ssn);
            // ifs >> gt >> pcode >> ssn;
            if (pcode == STP_PC && ssn != STP_SSN) {
                cout << "err: invalid ssn of stp. should be " << STP_SSN << endl;
                ifs.close();
                exit(1);
            }
            for (i = 0; i < gt.size(); ++i) gt[i] -= 48;
            gtt_table.insert(make_pair(gt, make_pair(pcode, ssn)));
        }
    }

    ifs.close();
}
