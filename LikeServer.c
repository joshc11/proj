#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

float RUNTIME = 5 * 60;

float elasped(struct timeval start){
	struct timeval current;
	gettimeofday(&current, NULL);
	return current.tv_sec - start.tv_sec;
}

int main (int argc, char **argv){
	char* name = argv[0];
	int count;
	struct timeval start;
	gettimeofday(&start, NULL);
	while (elasped(start) < RUNTIME){
		count = rand() % 43;
		printf("%s %d\n", name, count);
		sleep(rand() % 5 + 1);
	}
	return 0;
}
