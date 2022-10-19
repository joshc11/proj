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

int main(){
	char name[100];
	char* number;
	pid_t pid;
	for (int i = 1; i <= SERVER_COUNT; i++){
		pid = fork();
		*number = (char)i;
		strcpy(name, SERVER);
		strcat(name, number);
		if (pid < CHILD) {
			fprintf(stderr, ERROR_STRING);
			return ERROR;
		}
		if (pid == CHILD){
			execvp(FILE_NAME, name);
		}
	}
	return 0;
}
