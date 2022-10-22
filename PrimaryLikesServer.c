#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
const int PORT = 9000;
const int BUFFER = 100;
const int SERVER_COUNT = 10;
const char *LOG_FILE = "/tmp/PrimaryLikesLog";
const char *DELIMITER = " ";
const char *SUCCESS = "0";
int main (){
	FILE *log;
	char* client_name;
	char* count_string;
	int count;
	int total = 0;
	int network = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_port = htons(PORT);
	address.sin_addr.s_addr = INADDR_ANY;
	bind(network, (struct sockaddr*) &address, sizeof(address));
	listen(network, SERVER_COUNT);
	char message[BUFFER];
	int client = accept(network, NULL, NULL);
	//while(recv(client, &message, sizeof(message),0)!=0){
		recv(client, &message, sizeof(message),0);
//		send(network, SUCCESS, sizeof(SUCCESS), 0);
		client_name = strtok(message, DELIMITER);
		count_string = strtok(NULL, DELIMITER);
		count = atoi(count_string);
		total += count;
		printf("%s %d\n", client_name, count);
		printf("Total   %d\n", total);
//	}
	close(client);
	shutdown(network, SHUT_RDWR);
	return 0;
}
