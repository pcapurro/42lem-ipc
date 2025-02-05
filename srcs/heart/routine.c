#include "../../include/header.h"

void	printMap(tInfos* infos)
{
	for (int i = 0; infos->map[i] != '\0'; i++)
	{
		if (i % 16 == 0 && i != 0)
			printf("\n");
		printf("%c ", infos->map[i]);
	}
	printf("\n");
	printf("\n");
}

bool	isOver(tInfos* infos)
{
	if (infos->init == false)
	{
		if (infos->alive == false)
			return (true);
	}
	else
		;

	return (false);
}

bool	isNowDead(tInfos* infos)
{
	return (false);
}

void	startRoutine(tInfos* infos)
{
	printf("starting routine...\n");

	int k = 0;
	while (isOver(infos) == false)
	{
		if (infos->alive == true)
		{
			if (isNowDead(infos) == true)
				dieNow(infos);
			else
				moveNow(infos);
		}

		if (infos->init == true)
			printMap(infos);

		sleep(1);

		if (k == 7)
			break ;
		k++;
	}
}
