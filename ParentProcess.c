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

int main(){
	FILE *log;
	char name[BUFFER];
	static char * args[1];
	char number[BUFFER];
	pid_t pid;
	long children[SERVER_COUNT];
	for (int i = 0; i < SERVER_COUNT; i++){
		pid = fork();
		children[i] = (long)pid;
		sprintf(number, "%d", i);
		strcpy(name, SERVER);
		strcat(name, number);
		args[0] = name;
		if (pid < CHILD) {
			log = fopen(LOG_FILE, APPEND);
        	fprintf(log, "FAILED TO START %s\n", name);
        	fclose(log);
		}
		if (pid == CHILD){
			execvp(FILE_NAME, args);
		}
		log = fopen(LOG_FILE, APPEND);
        fprintf(log, "STARTED %s\n", name);
        fclose(log);
		sleep(1);
	}
	int status;
	for (int i = 0; i < SERVER_COUNT; i++){
		pid =  wait(&status);
		for (int i = 0; i < SERVER_COUNT; i++){
			if (children[i] == pid){
				sprintf(number, "%d", i);
        		strcpy(name, SERVER);
        		strcat(name, number);
				break;
			}
		}
		if (WIFEXITED(status)) {
			log = fopen(LOG_FILE, APPEND);
        	fprintf(log, "ENDED %s\n", name);
        	fclose(log);
		} else {
			log = fopen(LOG_FILE, APPEND);
        	fprintf(log, "ABORTED %s\n", name);
        	fclose(log);
		}
	}
	return 0;
}
