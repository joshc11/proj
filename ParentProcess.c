#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

const int SERVER_COUNT = 10;
const char* SERVER = "LikeServer";
const char* FILE_NAME = "./LikeServer";
const char* LOG_FILE = "/tmp/ParentProcessStatus";
const char* APPEND = "a";
const int CHILD = 0;
const int BUFFER = 30;
const char* CHILD_STRING = "Child";
const int SUCCESS = 0;

int main(){
	FILE *log;
	char name[BUFFER];
	char childId[BUFFER];
	static char * args[1];
	char number[BUFFER];
	pid_t pid;
	long children[SERVER_COUNT];
	for (int i = 0; i < SERVER_COUNT; i++){
		pid = fork();
		children[i] = (long)pid;
		sprintf(number, "%d", i);
		strcpy(childId, CHILD_STRING);
		strcpy(name, SERVER);
		strcat(childId, number);
		strcat(name, number);
		args[0] = name;
		if (pid < CHILD) {
			log = fopen(LOG_FILE, APPEND);
        	fprintf(log, "FAILED TO START %s\n", childId);
        	fclose(log);
		}
		if (pid == CHILD){
			execvp(FILE_NAME, args);
		}
		log = fopen(LOG_FILE, APPEND);
        fprintf(log, "STARTED %s\n", childId);
        fclose(log);
		sleep(1);
	}
	int status;
	for (int i = 0; i < SERVER_COUNT; i++){
		pid =  wait(&status);
		for (int i = 0; i < SERVER_COUNT; i++){
			if (children[i] == pid){
				sprintf(number, "%d", i);
        		strcpy(childId, CHILD_STRING);
        		strcat(childId, number);
				break;
			}
		}
		if (status == SUCCESS) {
			log = fopen(LOG_FILE, APPEND);
        	fprintf(log, "ENDED %s\n", childId);
        	fclose(log);
		} else {
			log = fopen(LOG_FILE, APPEND);
        	fprintf(log, "ENDED W/ ERROR %s\n", childId);
        	fclose(log);
		}
	}
	return 0;
}
