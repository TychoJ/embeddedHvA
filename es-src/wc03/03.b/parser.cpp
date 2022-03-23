#include "parser.hpp"
#include <cstdlib>
#include <cstring>
#include <cstdio>

Parser::Parser() {
	this->Command = NULL;
	this->commandNum = 0;
    this->varNum = 0;
    this->varList = NULL;
}

Parser::~Parser() {
	free(this->Command);
}

// return 1 if input is empty or invalid otherwise 0
int8_t Parser::parse(char *input) {
	this->commandNum = 0;	
	char *str;

	str = input;

    //TODO fix so that you can start with empty lines 
    //TODO add comments option
	while (*str == ' ' || *str == '\t')	str++;	// iterate through leading spaces
	if (*str == '\n' && *str == '\0') return 1; // return 1 if no command has been given

    // check var init
    char *ptr = str;
    uint32_t len;
    while (*str != ' ' && *str != '\n' && *str != '\0') str++;
    len = str - ptr;
    char *tmpStr = (char *)malloc(sizeof(char)*len);
    for (uint32_t i = 0; i < len; i++) {
        *(tmpStr+i) = *(ptr+i) < 91 ? *(ptr+i) + 32: *(ptr+i);
    }

    if (isVarInit(tmpStr) && !isVar(tmpStr)) 
        saveVar(tmpStr, str);
    else if (isVar(str - len));
    // else if (isCommand(str))


	while (*str != '\0' && *str != '\n') str++;	

    free(tmpStr);
    return 0;
}

uint16_t Parser::getCommand(char *command, uint8_t commandNum) {
    return 0;
}

//  
//  red <on><off>
//  led red <pin>
//  button stop <pin>
//  


//<32bits soort><32bits ident><bool>

// not valid = 0
// led     = 1
// button  = 2
// label   = 3
// 
uint32_t Parser::isVarInit(char *str){
    if (strcmp(str, "led") == 0) return LED;
    else if (strcmp(str, "button") == 0) return BUTTON;
    else if (strcmp(str, "label") == 0)  return LABEL;
    else return 0;
}

void Parser::saveVar(char *type, char *str){
    uint32_t len;

    // save var
    while (*str == ' ' || *str == '\t')	str++;	// iterate through leading spaces
	if (*str == '\n' && *str == '\0') exit(EXIT_FAILURE); // exit with failure if no argument has been given
    char *ptr = str;
    
    
    
    //get name
    while (*str != ' ' && *str != '\n' && *str != '\0') str++;
    len = str - ptr;
    char *tmpStr = (char *)malloc(sizeof(char) * (len + 1));
    for (uint32_t i = 0; i < len; i++) {
        tmpStr[i] = ptr[i];
    }
    tmpStr[len] = '\0';
    
    if (isVar(tmpStr)) {
        printf("variable: %s already exists\n", tmpStr);
        free(tmpStr);
        return;
    }
    
    this->varList = (var_t*)realloc(this->varList, sizeof(var_t) * (this->varNum + 1));
    this->varList[this->varNum].name = (char *)malloc(sizeof(char) * (len + 1)); 
    for (uint32_t i = 0; i < len; i++) {
        this->varList[this->varNum].name[i] = ptr[i];
    }
    this->varList[this->varNum].name[len] = '\0';

    this->varList[this->varNum].type = isVarInit(type);

    // get value
    if (this->varList[this->varNum].type != LABEL) {
        while (*str == ' ' || *str == '\n' || *str == '\0') str++;
        if (*str == '\n' && *str == '\0') exit(EXIT_FAILURE); // exit with failure if no argument has been given
        this->varList[this->varNum].pin = atoi(str);
    }

    this->varList[this->varNum].id = this->varNum;
    this->varNum++;

    free(tmpStr);
    //this->printVars();
}

// returns var type
// does not exist = 0
// led     = 1
// button  = 2
// label   = 3
uint32_t Parser::isVar(char *str){
    char *ptr = str;
    uint32_t len;

    // find token 0 [red 16 -> red] 
    while (*ptr != ' ' && *ptr != '\n' && *ptr != '\0') ptr++;
    len = ptr - str;

    for (uint32_t i = 0; i < this->varNum; i++) {
        if (strncmp(str, this->varList[i].name, len) == 0){
            return 1;
        }
    }
    return 0;
} 

void Parser::printVars(void){
    for (uint32_t i = 0; i < this->varNum; i++) {
        printf("var name:\t%s\n", this->varList[i].name);
        printf("var type:\t%d\n", this->varList[i].type);
        printf("var pin:\t%d\n", this->varList[i].pin);
        printf("var id:\t%d\n", this->varList[i].id);
        fflush(stdout);
    }
}