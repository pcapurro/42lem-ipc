#include "../../include/header.h"

void	startRoutine(tInfos* infos)
{
	int		k = 0;

	if (spawnNow(infos) != 0)
		return ;

	while (isOver(infos) == false)
	{
		updateMap(infos);
		if (infos->init == false || infos->coord != -1)
			moveNow(infos);

		getTeamsNumber(infos);
		getPlayersNumber(infos);
		if (infos->init == true)
			printMap(infos);

		sleep(1);
		if (k == 7)
			break ;
		k++;
	}
	if (infos->init == true)
		printMap(infos);

	if (infos->realMap[infos->coord] != '#' && infos->realMap[infos->coord] != '0')
		infos->realMap[infos->coord] = '0';

	while (infos->init == true && infos->playersNb != 0)
		getPlayersNumber(infos), usleep(500);
}
