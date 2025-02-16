#include "../../include/header.h"

void	spawnNow(tInfos* infos)
{
	infos->playersNb = getPlayersNumber(infos);
	if (infos->playersNb == 9)
		sem_post(infos->access), endFree(infos, 1);

	int	free = 0;

	for (int i = 0; infos->map[i] != '\0'; i++)
	{
		if (infos->map[i] == '0')
			free++;
	}

	if (free == 0)
		sem_post(infos->access), endFree(infos, 1);

	srand(time(NULL));
	int value = rand() % free;
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
	infos->map[infos->coord] = infos->team + 48;
}

void	getGameInfos(tInfos* infos)
{
	infos->teamsNb = getTeamsNumber(infos);
	infos->alliesNb = getAlliesNumber(infos);
	infos->playersNb = getPlayersNumber(infos);

	if (infos->init == true)
	{
		if (infos->teamsNb > 1 && infos->playersNb > infos->teamsNb \
			&& infos->state == false)
			infos->state = true;
	}
}

void	startRoutine(tInfos* infos)
{
	sem_wait(infos->access);
	spawnNow(infos);

	while (isOver(infos) == false)
	{
		if (infos->init == false || infos->coord != -1)
			moveNow(infos);

		getGameInfos(infos);
		if (infos->init == true)
			printMap(infos);

		sem_post(infos->access);
		sleep(1);
		sem_wait(infos->access);
	}

	if (infos->coord != -1)
	{
		if (infos->map[infos->coord] != '#' && infos->map[infos->coord] != '0')
			infos->map[infos->coord] = '0';
	}

	sem_post(infos->access);

	while (infos->init == true && infos->playersNb != 0)
	{
		printMap(infos);

		sem_wait(infos->access);
		infos->playersNb = getPlayersNumber(infos);
		sem_post(infos->access);

		sleep(1);
	}
}
