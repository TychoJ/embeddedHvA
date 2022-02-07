#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

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
	
	if (file =  fopen(fileName, "a") == NULL) {
		printf("Something went wrong");
		return EXIT_FAILURE;
	}
	
	fprintf(file, "%s:\t%s\n", asctime(localtime(&t)), log);

	fclose(file);

	return EXIT_SUCCESS;
}
