#include "../include/header.h"

void	printHelp(void)
{
	writeStr("Usage: ./42lem-ipc [team number]\n", 1);
	writeStr("Note: team number is limited from 1 to 10.\n\n", 1);

	writeStr("Players will battle on a 2D board. ", 1);
	writeStr("If a player is surrounded by at least 2 players of the same team, he dies.\n", 1);
	writeStr("The last team alive on the board wins the game.\n", 1);
}

bool	isHelp(const char* str)
{
	if (getStrLen(str) == 2)
	{
		if (str[0] == '-' && str[1] == 'h')
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
