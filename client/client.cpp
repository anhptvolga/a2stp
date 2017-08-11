#include "../su.h"
#include "../bitlib.h"
#include "../const.h"
#include <ctime>
#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>	

char *random_data() {
	char *d = (char *) malloc(20 * sizeof(char));
	d[19] = 0;
	for (int i = 0;i < 19; i++) {
		d[i] = rand() % 27 + 97;
	}
	return d;
}

void random_party_address(struct party_address &pa) {
	// indicator
	pa.indicator = 11;
	// random bit G
	if ((rand() % 10 + 1) % 2) {
		onbit(pa.indicator, 6);
	}
	// random point code 1001 - 2024
	int pc = rand() % 1025 + 1001;
	memcpy(pa.pointCode, int2buff(pc, 2), 2);
		
	// random subnumber 1-6
	pa.subNumber = rand() % 7 + 1;;
	// random global title
	int gt = rand() % 500 + 1;
	//printf("%d\n", gt);
	memcpy(pa.gt, int2buff(gt, 11), 11);

	// print party code
	/*
	printf("PA: ");
	bin_print_char(pa.indicator);
	printf(" ");
	bin_print_buff(pa.pointCode, 2);
	bin_print_char(pa.subNumber);
	printf(" ");
	bin_print_buff(pa.gt, 11);
	printf("\n");
	*/
}

// Randomly generate signal unit.
// Structure
// INDICATOR 8 bits - random bit G - bit 6
// Point code 2 bytes - take random from config file
// Subsystem number 4 bytes - take random from config file
// Global title 11 bytes - take random from config file
// Data - 20 bytes random
struct signal_unit generate_data() {
	
	struct signal_unit su;
	random_party_address(su.CgPA);
	random_party_address(su.CdPA);
	strcpy(su.data, random_data());

	return su;
}

// main loop. client will send data to server every 3s.
int main(int argc, char const *argv[]) {
	
	srand(time(NULL));
	
	// Connect to socket
	int sock;
	struct sockaddr_in server;

	// Create socket
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0) {
		printf("Could not create socket\n");
		exit(1);
	}
	printf("Socket created\n");

	// Config
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_family = AF_INET;
	server.sin_port = htons(8000);
	
	// Connect to server
	if (connect(sock, (struct sockaddr*)&server, sizeof(server))) {
		printf("Connect failed. Error\n");
		exit(1);
	}	

	printf("Connected\n");

	while (1) {
		// every 3 seconds
		sleep(3);
		
		const char *message = (const char *)malloc(SU_SIZE * sizeof(char));
		// generate data
		struct signal_unit su = generate_data();
		message = su_to_buffer(su);		


		// send data
		if (send(sock, message, SU_SIZE, 0) < 0) {	
			printf("Send failed\n");
			exit(1);
		}
		free((void *)message);
	}
	close(sock);
			
	return 0;
}
