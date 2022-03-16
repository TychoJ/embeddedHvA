
#include <cstdint>

#define LED 0


class Parser {
    public:
	    Parser();
	    ~Parser();
	    int8_t parse(char *input);
	    uint16_t getCommand(char *command, uint8_t commandNum);
    private:
        uint32_t isCommand(char *str);
	    uint8_t commandNum;
	    char **Command;
};