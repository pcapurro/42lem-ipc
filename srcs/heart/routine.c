#include "../../include/header.h"

void	spawnNow(tInfos* infos)
{
	int	free = 0, value = 0;

	for (int i = 0; infos->realMap[i] != '\0'; i++)
	{
		if (infos->realMap[i] == '0')
			free++;
	}

	if (free == 0)
		endFree(infos), exit(1);

	value = rand() % free;
	free = 0;

	for (int i = 0; infos->realMap[i] != '\0'; i++)
	{
		if (infos->realMap[i] == '0')
		{
			free++;
			if (free == value)
				infos->coord = i;
		}
	}
	infos->realMap[infos->coord] = infos->team + 48;
}

void	getGameInfos(tInfos* infos)
{
	infos->teamsNb = getTeamsNumber(infos->realMap);
	infos->alliesNb = getAlliesNumber(infos->realMap, infos->team);
	infos->playersNb = getPlayersNumber(infos->realMap);

	if (infos->init == true)
	{
		if (infos->teamsNb > 1 && infos->state == false)
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
		if (infos->realMap[infos->coord] != '#' && infos->realMap[infos->coord] != '0')
			infos->realMap[infos->coord] = '0';
	}

	sem_post(infos->access);

	while (infos->init == true && infos->playersNb != 0)
	{
		printMap(infos);
		sem_wait(infos->access);
		infos->playersNb = getPlayersNumber(infos->realMap);
		sem_post(infos->access);
		sleep(1);
	}
}
