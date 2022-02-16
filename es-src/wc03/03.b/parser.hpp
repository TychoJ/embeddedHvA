
#include <cstdint>

class Parser
{
private:
	uint8_t commandNum;
	char **Command;
public:
	Parser();
	~Parser();
	int8_t parse(char *input);
	uint16_t getCommand(char *command, uint8_t commandNum);
};