#include "../../include/header.h"

void	printMap(tInfos* infos)
{
	for (int i = 0; infos->realMap[i] != '\0'; i++)
	{
		if (i % 16 == 0 && i != 0)
			printf("\n");
		printf("%c ", infos->realMap[i]);
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
	int		centerX = 0, centerY = 0;
	char	center = '\0';
	char	up = '\0', down = '\0';
	char	left = '\0', right = '\0';

	centerX = infos->coord / MAP_WIDTH;
	centerY = infos->coord % MAP_WIDTH;

	center = infos->map[centerX][centerY];

	if (centerX != 0)
		up = infos->map[centerX - 1][centerY];

	if (centerX != MAP_HEIGHT - 1)
		down = infos->map[centerX + 1][centerY];

	if (centerY != 0)
		left = infos->map[centerX][centerY - 1];

	if (infos->map[centerX][centerY + 1] != '\0')
		right = infos->map[centerX][centerY + 1];

	if ((left > 48 && right > 48 && center != left && center != right)
		|| (up > 48 && down > 48 && up == down && center != up && center != down))
		return (true);

	if ((left > 48 && up > 48 && left == up && center != left && center != up)
		|| (right > 48 && up > 48 && right == up && center != right && center != up))
		return (true);

	if ((left > 48 && down > 48 && left == down && center != left && center != down)
		|| (right > 48 && down > 48 && right == down && center != right && center != down))
		return (true);

	return (false);
}

void	updateMap(tInfos* infos)
{
	for (int i = 0, j = 0; infos->map[i] != NULL; i++)
	{
		for (int k = 0; infos->map[i][k] != '\0'; k++, j++)
			infos->map[i][k] = infos->realMap[j];
	}
}

void	startRoutine(tInfos* infos)
{
	int	k = 0;
	printf("starting routine...\n");

	spawnNow(infos);
	while (isOver(infos) == false)
	{
		if (infos->alive == true)
		{
			updateMap(infos);

			if (isNowDead(infos) == true)
			{
				printf("dying now...\n");
				infos->alive = false;
				infos->realMap[infos->coord] = '0';
			}
			else
				moveNow(infos);
		}

		if (infos->init == true)
			printMap(infos);

		sleep(1);

		if (k == 2)
			break ;
		k++;
	}
}
