#include "../../include/header.h"

void	move(tInfos* infos, const int newCoord)
{
	infos->realMap[infos->coord] = '0';
	infos->realMap[newCoord] = infos->team + 48;
	infos->coord = newCoord;
}

void	*moveLeft(tInfos* infos)
{
	int	centerX = infos->coord / MAP_WIDTH;
	int	centerY = infos->coord % MAP_WIDTH;

	if ((centerY - 1) < 0)
		return (NULL);

	int newCoord = (centerX * MAP_WIDTH) + (centerY - 1);
	if (infos->realMap[newCoord] != '0')
		return (NULL);

	move(infos, newCoord);

	return (infos);
}

void	*moveRight(tInfos* infos)
{
	int	centerX = infos->coord / MAP_WIDTH;
	int	centerY = infos->coord % MAP_WIDTH;

	if (infos->map[centerX][centerY + 1] == '\0')
		return (NULL);

	int newCoord = (centerX * MAP_WIDTH) + (centerY + 1);
	if (infos->realMap[newCoord] != '0')
		return (NULL);
	move(infos, newCoord);

	return (infos);
}

void	*moveUp(tInfos* infos)
{
	int	centerX = infos->coord / MAP_WIDTH;
	int	centerY = infos->coord % MAP_WIDTH;

	if (centerX - 1 == 0)
		return (NULL);

	int newCoord = ((centerX - 1) * MAP_WIDTH) + centerY;
	if (infos->realMap[newCoord] != '0')
		return (NULL);
	move(infos, newCoord);

	return (infos);
}

void	*moveDown(tInfos* infos)
{
	int	centerX = infos->coord / MAP_WIDTH;
	int	centerY = infos->coord % MAP_WIDTH;

	if (infos->map[centerX + 1] == NULL)
		return (NULL);

	int newCoord = ((centerX + 1) * MAP_WIDTH) + centerY;
	if (infos->realMap[newCoord] != '0')
		return (NULL);
	move(infos, newCoord);

	return (infos);
}

void	*moveLeftUp(tInfos* infos)
{
	int	centerX = infos->coord / MAP_WIDTH;
	int	centerY = infos->coord % MAP_WIDTH;

	if ((centerX - 1) < 0 || (centerY - 1) < 0)
		return (NULL);

	int newCoord = ((centerX - 1) * MAP_WIDTH) + (centerY - 1);
	if (infos->realMap[newCoord] != '0')
		return (NULL);
	move(infos, newCoord);

	return (infos);
}

void	*moveRightUp(tInfos* infos)
{
	int	centerX = infos->coord / MAP_WIDTH;
	int	centerY = infos->coord % MAP_WIDTH;

	if ((centerX - 1) < 0 || infos->map[centerX][centerY + 1] == '\0')
		return (NULL);

	int newCoord = ((centerX - 1) * MAP_WIDTH) + (centerY + 1);
	if (infos->realMap[newCoord] != '0')
		return (NULL);
	move(infos, newCoord);

	return (infos);
}

void	*moveLeftDown(tInfos* infos)
{
	int	centerX = infos->coord / MAP_WIDTH;
	int	centerY = infos->coord % MAP_WIDTH;

	if (infos->map[centerX + 1] == NULL || (centerY - 1) < 0)
		return (NULL);

	int newCoord = ((centerX + 1) * MAP_WIDTH) + (centerY - 1);
	if (infos->realMap[newCoord] != '0')
		return (NULL);
	move(infos, newCoord);

	return (infos);
}

void	*moveRightDown(tInfos* infos)
{
	int	centerX = infos->coord / MAP_WIDTH;
	int	centerY = infos->coord % MAP_WIDTH;

	if (infos->map[centerX + 1] == NULL || infos->map[centerX][centerY + 1] == '\0')
		return (NULL);

	int newCoord = ((centerX + 1) * MAP_WIDTH) + (centerY + 1);
	if (infos->realMap[newCoord] != '0')
		return (NULL);
	move(infos, newCoord);

	return (infos);
}

void	moveRandomly(tInfos* infos)
{
	int	value = rand() % 8;

	printf("moving randomly\n");

	if (value == 0)
		moveLeft(infos);

	if (value == 1)
		moveRight(infos);

	if (value == 2)
		moveUp(infos);

	if (value == 3)
		moveDown(infos);

	if (value == 4)
		moveLeftUp(infos);

	if (value == 5)
		moveRightUp(infos);

	if (value == 6)
		moveLeftDown(infos);

	if (value == 7)
		moveRightDown(infos);
}

void	moveTowardsTarget(tInfos* infos, const int target)
{
	int	x = infos->coord % MAP_WIDTH;
	int y = infos->coord / MAP_WIDTH;

	int targetX = target % MAP_WIDTH;
	int targetY = target / MAP_WIDTH;

	if (x > targetX && y > targetY)
		moveLeftUp(infos);
	else if (x > targetX && y < targetY)
		moveLeftDown(infos);

	else if (x < targetX && y > targetY)
		moveRightUp(infos);
	else if (x < targetX && y < targetY)
		moveRightDown(infos);

	else if (x == targetX && y > targetY)
		moveUp(infos);
	else if (x == targetX && y < targetY)
		moveDown(infos);

	else if (x > targetX && y == targetY)
		moveLeft(infos);
	else if (x < targetX && y == targetY)
		moveRight(infos);
}

void	moveNow(tInfos* infos)
{
	if (infos->teamsNb == 1 || infos->alliesNb <= 1)
		{ moveRandomly(infos); return ; }

	int target = getLastTarget(infos);

	if (target == -1)
		target = createNewTarget(infos);
	else
	{
		if (infos->realMap[target] == '0')
		{
			target = retrieveLastTarget(infos);
			if (target == -1)
				target = createNewTarget(infos);
		}
	}

	if (target != -1)
	{
		infos->lastTarget = infos->target;
		infos->target = target;

		sendNewTarget(infos, target);
		moveTowardsTarget(infos, target);
	}
	else
		moveRandomly(infos);
}
