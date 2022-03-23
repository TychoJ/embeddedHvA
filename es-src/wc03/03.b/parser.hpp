
#include <cstdint>

#define LED 1
#define BUTTON 2
#define LABEL  3

typedef struct {
    char *name;
    uint32_t type;
    uint32_t id;
    uint32_t pin;
}var_t;


class Parser {
    public:
	    Parser();
	    ~Parser();
	    int8_t parse(char *input);
        void printVars(void);
	    uint16_t getCommand(char *command, uint8_t commandNum);
    private:
        uint32_t isVarInit(char *str);
        void saveVar(char *type, char *str);
        uint32_t isVar(char *str);
	    uint8_t commandNum;
	    char **Command;
        var_t *varList;
        uint32_t varNum;
};