#include "../../include/header.h"

void	printColor(const int team)
{
	if (team == 1)
		printf("\033[31m");

	if (team == 2)
		printf("\033[32m");

	if (team == 3)
		printf("\033[33m");

	if (team == 4)
		printf("\033[34m");

	if (team == 5)
		printf("\033[35m");

	if (team == 6)
		printf("\033[36m");

	if (team == 7)
		printf("\033[37m");

	if (team == 8)
		printf("\033[38;5;220m");

	if (team == 9)
		printf("\033[38;5;94m");
}

void	printMap(tInfos* infos)
{
	const char*	alphabet = "abcdefghijklmnopqrstuvwxyz";

	printf("\033[H\033[J");
	printf("– 42lem-ipc –\n\n");

	printf("Players: %d\n", infos->playersNb);
	printf("Teams: %d\n", infos->teamsNb);
	printf("Game map: \n\n");

	printf("    ");
	for (int i = 0; i != MAP_WIDTH + 1; i++)
		printf("───");
	printf("\n");

	printf(" 1 ");
	if (MAP_HEIGHT >= 10)
		printf(" ");
	printf("│");

	for (int i = 0, k = 0; infos->realMap[i] != '\0'; i++)
	{
		if (i % MAP_WIDTH == 0 && i != 0)
		{
			if (MAP_HEIGHT >= 10 && k + 2 < 10)
				printf(" │\n %d  │", k + 2);
			else
				printf(" │\n %d │", k + 2);
			k++;
		}
		if (infos->realMap[i] == '#' || infos->realMap[i] == '0')
			printf(" 0 ");
		else
		{
			if (infos->realMap[i] == '%')
			{
				printf(" ");
				printf("\033[31mf\033[0m ");
			}
			else
			{
				printf(" ");
				printColor(infos->realMap[i] - 48);
				printf("%c\033[0m ", infos->realMap[i]);
			}
		}
	}
	printf(" │\n    ");
	for (int i = 0; i != MAP_WIDTH + 1; i++)
		printf("───");
	
	printf("\n    ");
	if (MAP_HEIGHT >= 10)
		printf(" ");

	for (int i = 0; alphabet[i] != '\0' && i != MAP_WIDTH; i++)
		printf(" %c ", alphabet[i]);
	printf("\n–\n");
}
