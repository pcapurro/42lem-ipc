#include "../../include/header.h"

void	printMap(tInfos* infos)
{
	const char*	alphabet = "abcdefghijklmnopqrstuvwxyz\1";

	printf("\033[H\033[J");
	printf("– 42lem-ipc –\n\n");

	printf("Number of players: %d\n", infos->playersNb);
	printf("Number of teams: %d\n", infos->teamsNb);
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
		printf(" %c ", infos->realMap[i]);
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

void	updateMap(tInfos* infos)
{
	for (int i = 0, j = 0; infos->map[i] != NULL; i++)
	{
		for (int k = 0; infos->map[i][k] != '\0'; k++, j++)
			infos->map[i][k] = infos->realMap[j];
	}
}
