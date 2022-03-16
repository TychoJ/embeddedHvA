#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define NUM_LOOPS 1000
#define BUF_SIZE 4096
int main(void) {
	char cmd[BUF_SIZE];
	for (uint16_t i = 0; i < NUM_LOOPS; i++) {
		sprintf(cmd, "./log test.log %d", i);
		system(cmd);
		sprintf(cmd, "./log test.log %d", i*i);
		system(cmd);
	}
	return 0;
}
