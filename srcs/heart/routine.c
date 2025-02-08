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
	infos->teamsNb = getTeamsNumber(infos->map);
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
	int		k = 0;

	spawnNow(infos);

	while (isOver(infos) == false)
	{
		updateMap(infos);
		if (infos->init == false || infos->coord != -1)
			moveNow(infos);

		getGameInfos(infos);
		if (infos->init == true)
			printMap(infos);

		sleep(1);
		if (k == 7)
			break ;
		k++;
	}

	if (infos->realMap[infos->coord] != '#' && infos->realMap[infos->coord] != '0')
		infos->realMap[infos->coord] = '0';

	while (infos->init == true && infos->playersNb != 0)
	{
		printMap(infos);
		infos->playersNb = getPlayersNumber(infos->realMap);
		sleep(1);
	}
}
