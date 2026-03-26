#pragma once

#include <string>


#define C_FG_BLACK_CODE   "\033[30m"
#define C_FG_RED_CODE	"\033[31m"
#define C_FG_GREEN_CODE   "\033[32m"
#define C_FG_YELLOW_CODE  "\033[33m"
#define C_FG_BLUE_CODE	"\033[34m"
#define C_FG_MAGENTA_CODE "\033[35m"
#define C_FG_CYAN_CODE	"\033[36m"
#define C_FG_WHITE_CODE   "\033[37m"
#define C_RESET "\e[0m"

typedef enum e_logType {
	LOG_INFO,
	LOG_ERROR,
	LOG_DEBUG,
	LOG_WARNING
}				t_logType;


void    newLog(std::string s, int log_type);
