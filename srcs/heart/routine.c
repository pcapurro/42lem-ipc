#include "../../include/header.h"

void	getNewPosition(tInfos* infos)
{
	int	free = 0, value = 0;

	for (int i = 0; infos->map[i] != '\0'; i++)
	{
		if (infos->map[i] == '0')
			free++;
	}

	value = rand() % free;
	free = 0;

	for (int i = 0; infos->map[i] != '\0'; i++)
	{
		if (infos->map[i] == '0')
		{
			free++;
			if (free == value)
				infos->coord = i;
		}
	}
}

void	getToNextPosition(tInfos* infos)
{
	if (infos->coord == -1)
		getNewPosition(infos);
	else
	{
		tMsg	data;

		if (msgrcv(infos->msgId, &data, sizeof(data) - sizeof(long), infos->team, 0) == -1)
		{
			if (errno != EAGAIN && errno != EWOULDBLOCK)
				perror("42lem-ipc: "), endFree(infos), exit(1);
			else
				order(infos);
		}
		else
			executeOrder(infos, data.info);
	}

	infos->map[infos->coord] = infos->team + 48;
}

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

void	startRoutine(tInfos* infos)
{
	printf("starting routine...\n");

	int k = 0;
	while (1)
	{
		if (infos->init == true)
			printMap(infos);

		getToNextPosition(infos);
		sleep(1);

		if (k == 7)
			break ;
		k++;
	}
}
