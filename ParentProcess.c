#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

const int SERVER_COUNT = 10;
const char* SERVER = "LikeServer";
const char* ERROR_STRING = "Child Server failed to start";
const char* FILE_NAME = "./LikeServer";
const int CHILD = 0;
const int ERROR = 1;
const int BUFFER = 30;
int main(){
	char name[BUFFER];
	static char * args[1];
	char number[BUFFER];
	pid_t pid;
	for (int i = 1; i <= SERVER_COUNT; i++){
		pid = fork();
		sprintf(number, "%d", i);
		strcpy(name, SERVER);
		strcat(name, number);
		args[0] = name;
		if (pid < CHILD) {
			fprintf(stderr, ERROR_STRING);
			return ERROR;
		}
		if (pid == CHILD){
			execvp(FILE_NAME, args);
		}
	}
	return 0;
}
