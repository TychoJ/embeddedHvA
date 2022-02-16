#include "parser.hpp"
#include <cstdlib>
#include <cstring>

Parser::Parser() {
	this->Command = NULL;
	this->commandNum = 0;
}

Parser::~Parser() {
	free(this->Command);
}

// return 1 if input is empty or invalid otherwise 0
int8_t Parser::parse(char *input) {
	this->commandNum = 0;	
	char *ptr;

	ptr = input;

	while (*ptr == ' ')	ptr++;	// iterate through leading spaces

	if (*ptr == '\n') return 1; // return 1 if no command has been given

	while (*ptr != '\0') {
		this->commandNum++;
		while (*ptr != ' ' && *ptr != '\n' && *ptr != '\0') ptr++;
		while (*ptr == ' ')	ptr++;	// iterate through spaces
	}
	
	this->Command = (char **) malloc(sizeof(char*) * this->commandNum);
	
}

uint16_t Parser::getCommand(char *command, uint8_t commandNum) {

}
