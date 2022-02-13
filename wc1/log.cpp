#include "log.hpp"
#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cstring>
#include <ctime>
#include <cerrno>

#if defined(__linux__) || defined(__FreeBSD__)

	#include <unistd.h>
	#include <sys/stat.h>
	#include <sys/types.h>
	#include <sys/time.h>

#else

#include <windows.h>
#include <fileapi.h>

// MSVC defines this in winsock2.h!?
typedef struct timeval {
    long tv_sec;
    long tv_usec;
} timeval;

int gettimeofday(struct timeval * tp, struct timezone * tzp)
{
    // Note: some broken versions only have 8 trailing zero's, the correct epoch has 9 trailing zero's
    // This magic number is the number of 100 nanosecond intervals since January 1, 1601 (UTC)
    // until 00:00:00 January 1, 1970 
    static const uint64_t EPOCH = ((uint64_t) 116444736000000000ULL);

    SYSTEMTIME  system_time;
    FILETIME    file_time;
    uint64_t    time;

    GetSystemTime( &system_time );
    SystemTimeToFileTime( &system_time, &file_time );
    time =  ((uint64_t)file_time.dwLowDateTime )      ;
    time += ((uint64_t)file_time.dwHighDateTime) << 32;

    tp->tv_sec  = (long) ((time - EPOCH) / 10000000L);
    tp->tv_usec = (long) (system_time.wMilliseconds * 1000);
    return 0;
}

#endif

char errorString[512];

Log::Log(char *name) {
	this->setPath("");
	this->setName(name);
	this->setExtension("");
}

Log::Log(char *name, char *path) {
	this->setPath(path);
	this->setName(name);
	this->setExtension("");
}

Log::Log(char *name, char *extension, uint8_t onlyNeededForFunctionOverloadingThisDoesntDoAnyThingForTheCode) {
	this->setPath("");
	this->setName(name);
	this->setExtension(extension);
}

Log::Log(char *name, char *path, char *extension) {
	this->setPath(path);
	this->setName(name);
	this->setExtension(extension);
}

Log::~Log() {
	free(this->completePath);
	free(this->path);
	free(this->name);
	free(this->extension);
}

uint8_t Log::setPath(char *path) {
	if (*path == '\0') {
		this->path = (char *)malloc(sizeof(char)*1);
		this->path = "\0";
		return 1;
	} 
	uint16_t len = strlen(path);
	this->path = (char *)malloc(sizeof(char)*(len + 1));
	strcpy(this->path, path);
	strcat(this->path, "/");
	return 0;
}

uint8_t Log::setName(char *name) {
	if (*name == '\0') {
		this->name = (char *)malloc(sizeof(char)*5);
		this->name = "log";
		return 1;
	} 
	uint16_t len = strlen(name);
	this->name = (char *)malloc(sizeof(char)*len);
	strcpy(this->name, name);
	return 0;
}

uint8_t Log::setExtension(char *extension) {
	if (*extension == '\0') {
		this->extension = (char *)malloc(sizeof(char)*5);
		this->extension = ".log";
		return 1;
	} 
	uint16_t len = strlen(extension);
	this->extension = (char *)malloc(sizeof(char)*len);
	strcpy(this->extension, extension);
	return 0;
}

uint8_t Log::setCompletePath() {
	uint32_t len = strlen(this->path) + strlen(this->name) + strlen(this->extension);
	this->completePath = (char *)malloc(sizeof(char) * len);
	if (this->completePath == NULL) return 1;

	strcpy(this->completePath, this->path);
	strcat(this->completePath, this->name);
	strcat(this->completePath, this->extension);
	
	return 0;
}

uint8_t Log::openFile() {
	printf("path = %s\n", this->path);
	printf("name = %s\n", name);
	printf("ext  = %s\n", this->extension);


	this->setCompletePath();
	printf("file = %s\n", this->completePath);

	//if ((this->f = fopen(this->completePath, "r"))) {
	//	if ( (this->f = fopen(this->completePath, "w")) == NULL) {
	//		printf("Failed to open file. error %d\n");
	//		perror(errorString);
   	//		printf("%s\n", errorString);
	//	}
	//	fclose(this->f);
	//}	

#if defined(__linux__) || defined(__FreeBSD__)

	struct stat st = {0};

	if (stat(this->path, &st) == -1) {
    	mkdir(this->path, 0744);
	}

#else

	CreateDirectory(this->path, NULL);

#endif	
	
	this->f = fopen(this->completePath, "a");
	
	if (this->f == NULL) {
		printf("Failed to open file. error %d\n", errno);
		perror(errorString);
   		printf("%s\n", errorString);
		printf("how\n");
		return 1;
	}
	return 0;
}

uint8_t Log::closeFile() {
	fclose(this->f);
	return 0;
}

int8_t Log::log(char *str) {
	struct timeval tv;
	time_t t;

	gettimeofday(&tv, NULL);
    t = tv.tv_sec;

	char *time = asctime(localtime(&t));
	//printf("hi \n");
	//char *ptr;
	//ptr = strchr(time, '\n');
	//printf("hi \n");
	//time[ptr - time] = '\0';
	//printf("hi \n");
	strtok(time, "\n");
	this->openFile();
	fprintf(this->f, "%s:\t%s\n", time, str);
	fclose(this->f);
}
