#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/time.h>

#define BUF_TIME

int main(int argc, char *argv[]) {
	char *fileName;
	char *log;

	FILE *file;

	struct timeval tv;
	time_t t;

	gettimeofday(&tv, NULL);
	t = tv.tv_sec;

	if (argc < 3) {
		printf("ERROR use ./log <FILE-NAME> <LOG-MESSAGE>");
		return EXIT_FAILURE;
	}

	fileName = argv[1];
	log	= argv[2];
	
	file =  fopen(fileName, "a");
	if (file == NULL) {
		printf("Something went wrong");
		return EXIT_FAILURE;
	}
	
	char *time = asctime(localtime(&t));
	char *ptr = strchr(time, '\n');
	time[ptr - time] = '\0';

	fprintf(file, "%s:\t%s\n", time, log);

	fclose(file);

	return EXIT_SUCCESS;
}
