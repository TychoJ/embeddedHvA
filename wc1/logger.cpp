#include <cstdio>
#include "log.hpp"

int main(void) {
	Log logi("logiFromTheForLoop", "testCppLogger");
	//Log logi("testExample");
	//Log logii("logii", "testCppLoger");
	char log[4096];

	for (uint16_t i = 0; i < 10; i++) {
		sprintf(log, "%d", i);
		printf("i = %d\n", i);
		logi.log(log);
		//sprintf(log, "%d", i*i);
		//logii.log(log);
	}
	
	return 0;
}
