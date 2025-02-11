#include "../../include/header.h"

void	printColor(const int team)
{
	if (team == 1)
		writeStr("\033[31m", 1);
	if (team == 2)
		writeStr("\033[32m", 1);

	if (team == 3)
		writeStr("\033[33m", 1);
	if (team == 4)
		writeStr("\033[34m", 1);

	if (team == 5)
		writeStr("\033[35m", 1);
	if (team == 6)
		writeStr("\033[36m", 1);

	if (team == 7)
		writeStr("\033[37m", 1);
	if (team == 8)
		writeStr("\033[38;5;220m", 1);

	if (team == 9)
		writeStr("\033[38;5;94m", 1);
}

void	printMap(tInfos* infos)
{
	char	value = '\0';

	writeStr("\033[H\033[J", 1);
	writeStr("– 42lem-ipc –\n\n", 1);

	value = infos->playersNb + 48;
	writeStr("Players: ", 1), write(1, &value, sizeof(char));
	value = infos->teamsNb + 48;
	writeStr("\nTeams: ", 1), write(1, &value, sizeof(char));

	writeStr("\n\nGame map: \n\n   ", 1);

	for (int i = 0; i != MAP_WIDTH; i++)
		writeStr("───", 1);
	writeStr("\n  │", 1);

	for (int i = 0; infos->map[i] != '\0'; i++)
	{
		if (i % MAP_WIDTH == 0 && i != 0)
			writeStr("│\n  │", 1);

		if (infos->map[i] <= 48)
			writeStr(" 0 ", 1);
		else
		{
			writeStr(" ", 1);
			printColor(infos->map[i] - 48);
			write(1, &infos->map[i], sizeof(char));
			writeStr("\033[0m ", 1);
		}
	}
	writeStr("│\n   ", 1);
	for (int i = 0; i != MAP_WIDTH; i++)
		writeStr("───", 1);
	writeStr("\n    \n–\n", 1);
}
