#include "../include/header.h"

void	printHelp(void)
{
	writeStr("Usage: ./42lem-ipc ...\n", 1);
}

bool	isHelp(const char* str)
{
	if (getStrLen(str) == 5)
	{
		if (str[0] == '-' && str[1] == 'h' && str[2] == 'e' \
			&& str[3] == 'l' && str[4] == 'p')
			return (true);
	}

	if (getStrLen(str) == 6)
	{
		if (str[0] == '-' && str[1] == '-' && str[2] == 'h' \
			&& str[3] == 'e' && str[4] == 'l' && str[5] == 'p')
			return (true);
	}

	return (false);
}
