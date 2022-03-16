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
	char *str;

	str = input;

	while (*str == ' ' || *str == '\t')	str++;	// iterate through leading spaces
	if (*str == '\n' && *str == '\0') return 1; // return 1 if no command has been given

    char *ptr = str;
    char *tmpStr;
    uint32_t len;
    // get sort of command
    while (*str != ' ' && *str != '\n' && *str != '\0') str++;
    len = str - ptr;
    tmpStr = (char *)malloc(sizeof(char)*len);
    for (uint32_t i = 0; i < len; i++) {
        *(tmpStr+i) = *(ptr+i) < 91 ? *(ptr+i) + 32: *(ptr+i);
    }
    isCommand(tmpStr);
    

	while (*str != '\0') {
		this->commandNum++;
		while (*str != ' ' && *str != '\n' && *str != '\0') str++;
		while (*str == ' ' || *str == '\t')	str++;	// iterate through spaces
	}
	
	this->Command = (char **) malloc(sizeof(char*) * this->commandNum);
	
}

uint16_t Parser::getCommand(char *command, uint8_t commandNum) {

}

uint32_t Parser::isCommand(char *str){
    if (strcmp(str, "led") == 0) return 1;
    else if (strcmp(str, "button") == 0) return 2;
    else if (strcmp(str, "label") == 0)  return 3;
    else return 0;
}
//  
//  red <on><off>
//  led red = <pin>
//  button stop = <pin>
//  stop 


//<32bits soort><32bits ident><bool>

// not valid = 0
// led     = 1
// button  = 2
// label   = 3
// 