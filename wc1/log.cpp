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

	printf("1\n");
	strcpy(this->completePath, this->path);
	printf("2\n");
	strcat(this->completePath, this->name);
	printf("3\n");
	strcat(this->completePath, this->extension);
	printf("4\n");

	return 0;
}

uint8_t Log::openFile() {
	printf("path = %s\n", this->path);
	printf("name = %s\n", name);
	printf("ext  = %s\n", this->extension);

	this->setCompletePath();
	printf("file = %s\n", this->completePath);

	printf("Creating a directory\n");
    	mkdir(this->path, 0744);
	printf("created a drirectory\n");
	
	this->f = fopen(this->completePath, "a");
	
	printf("opened the file\n");

	if (this->f == NULL) {
		printf("Failed to open file. error %d\n", errno);
		perror(errorString);
   		printf("%s\n", errorString);
		printf("how\n");
		return 1;
	}
	printf("returning\n");
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
	strtok(time, "\n");
	this->openFile();
	printf("started writing to the file\n");

	uint16_t len = strlen(time);
	for (uint16_t i = 0; i < len; i++) {
		fputc(*time+i ,this->f);
	}

	fputc('\t', this->f);

	len = strlen(str);
	for (uint16_t i = 0; i < len; i++) {
		fputc(*str+i ,this->f);
	}
	
	printf("ended writing to the file\n");
	fclose(this->f);
	printf("closed the file\n");
}
