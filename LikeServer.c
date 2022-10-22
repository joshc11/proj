#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

const float RUNTIME = .5 * 60;
const char *APPEND = "a";
const char *DIRECTORY = "/tmp/";
const int BUFFER = 100;
const int PORT = 9000;

float elasped(struct timeval start){
	struct timeval current;
	gettimeofday(&current, NULL);
	return current.tv_sec - start.tv_sec;
}

int main (int argc, char **argv){
	int remote, server;
	if((server = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		abort();
	};
	struct sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_port = htons(PORT);
	address.sin_addr.s_addr = INADDR_ANY;
	if ((remote = connect(server, (struct sockaddr*) &address, sizeof(address))) == -1){
		abort();
	};
	char* name = argv[1];
	int count;
	char message[BUFFER];
	FILE *log;
	char fileName[BUFFER];
	strcpy(fileName, DIRECTORY);
	strcat(fileName, name);
	struct timeval start;
	gettimeofday(&start, NULL);
	srand((int)start.tv_sec);

	while (elasped(start) < RUNTIME){
		count = rand() % 43;
		sprintf(message,"%s %d", name, count);
		send(server, message, sizeof(message),0);
		sprintf(message,"1");
		recv(remote, &message, sizeof(message), 0);
		log = fopen(fileName, APPEND);
		fprintf(log, "Likeserver %d %s\n", count, message);
		fclose(log);
		sleep(rand() % 5 + 1);
	}
	close(remote);
	return 0;
}
