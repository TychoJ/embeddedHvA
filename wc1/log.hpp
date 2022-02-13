#include <cstdint>
#include <cstdio>

class Log
{
private:
	FILE *f;
	char *path;
	char *name;
	char *extension;
	char *completePath;

	uint8_t setPath(char *path);
	uint8_t setName(char *name);
	uint8_t setExtension(char *extension);
	uint8_t setCompletePath();
	uint8_t openFile();
	uint8_t closeFile();

public:
	Log(char *name);
	Log(char *name, char *path);
	Log(char *name, char *extension, uint8_t onlyNeededForFunctionOverloadingThisDoesntDoAnyThingForTheCode);
	Log(char *name, char *path, char *extension);
	~Log();
	int8_t log(char *str); //<! log string with length len. str length max is 65535 characters
};

