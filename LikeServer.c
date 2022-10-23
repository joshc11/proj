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
const char *SUCCESS = "0";

float elasped(struct timeval start){
	struct timeval current;
	gettimeofday(&current, NULL);
	return current.tv_sec - start.tv_sec;
}

int main (int argc, char **argv){
	int error = 0;
	int remote, server;
	struct sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_port = htons(PORT);
	address.sin_addr.s_addr = INADDR_ANY;

	char* name = argv[0];
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
		if(((server = socket(AF_INET, SOCK_STREAM, 0)) < 0) || (connect(server, (struct sockaddr*) &address, sizeof(address)) < 0)){
       		log = fopen(fileName, APPEND);
        	fprintf(log, "Likeserver %d 1\n", count);
        	fclose(log);
			error = 1;
    	} else {
			send(server, message, sizeof(message), 0);
			recv(server, &message, sizeof(message), 0);
			if(strcmp(message, SUCCESS)){
				sprintf(message,"1");
				error = 1;
			}
			log = fopen(fileName, APPEND);
			fprintf(log, "Likeserver %d %s\n", count, message);
			fclose(log);
		}
		sleep(rand() % 5 + 1);
	}
	if (error){exit(error);}
	return 0;
}
