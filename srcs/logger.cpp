#include <string>
#include <logger.h>
#include <iostream>

void	newLog(std::string s, int log_type)
{
	switch (log_type)
	{
		case LOG_INFO:
			std::cout << C_FG_GREEN_CODE << "[INFO]	";
			break;
		case LOG_ERROR:
			std::cout << C_FG_RED_CODE << "[ERROR]	";
			break;
		case LOG_DEBUG:
            std::cout << C_FG_BLUE_CODE  << "[DEBUG]	";
			break;
		case LOG_WARNING:
			std::cout << C_FG_YELLOW_CODE << "[WARNING]";
			break;
		default:
			break;
	}
	std::cout << "	" << s << C_RESET << '\n';

}

