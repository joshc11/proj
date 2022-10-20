#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include nelnet/in.h>
int main (){
	int network;
	network = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(9002);
	server.sin_addr.s_addr = INADDR_ANY;
	int status = connect(network, (struct sockaddr *), &server, sizeof(server));
	if (status == 1){printf("funy");}
	char message[100];
	recv(network, &message, sizeof(message));
	printf("%s", message);
	close(network);
	return 0;
}
