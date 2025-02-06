#include "../../include/header.h"

void	startRoutine(tInfos* infos)
{
	int		k = 0;

	spawnNow(infos);
	while (isOver(infos) == false)
	{
		if (infos->alive == true)
		{
			updateMap(infos);

			if (isNowDead(infos) == true)
				infos->alive = false, infos->realMap[infos->coord] = '0';
			else
				moveNow(infos);
		}

		if (infos->init == true)
		{
			getPlayersNumber(infos);
			getTeamsNumber(infos);
			printMap(infos);
		}
		sleep(1);

		if (k == 2)
			break ;
		k++;
	}
}
