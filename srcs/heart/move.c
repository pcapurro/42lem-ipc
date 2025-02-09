#include "../../include/header.h"

void	move(tInfos* infos, const int newCoord)
{
	if (infos->realMap[newCoord] != '0')
		return ;

	infos->realMap[infos->coord] = '0';
	infos->realMap[newCoord] = infos->team + 48;
	infos->coord = newCoord;
}

void	*moveLeft(tInfos* infos)
{
	if (infos->coord == 0 || infos->coord % MAP_WIDTH == 0)
		return (NULL);

	move(infos, infos->coord - 1);

	return (infos);
}

void	*moveRight(tInfos* infos)
{
	if (infos->coord + 1 >= getStrLen(infos->realMap) \
		|| (infos->coord + 1) % MAP_WIDTH == 0)
		return (NULL);

	move(infos, infos->coord + 1);

	return (infos);
}

void	*moveUp(tInfos* infos)
{
	if (infos->coord - MAP_WIDTH < 0)
		return (NULL);

	move(infos, infos->coord - MAP_WIDTH);

	return (infos);
}

void	*moveDown(tInfos* infos)
{
	if (infos->coord + MAP_WIDTH >= getStrLen(infos->realMap))
		return (NULL);

	move(infos, infos->coord + MAP_WIDTH);

	return (infos);
}

void	*moveLeftUp(tInfos* infos)
{
	if (infos->coord - MAP_WIDTH - 1 < 0 || infos->coord % MAP_WIDTH == 0)
		return (NULL);

	move(infos, infos->coord - MAP_WIDTH - 1);

	return (infos);
}

void	*moveRightUp(tInfos* infos)
{
	if ((infos->coord - MAP_WIDTH) + 1 < 0 \
		|| (infos->coord - MAP_WIDTH) + 1 >= getStrLen(infos->realMap) \
		|| (infos->coord + 1) % MAP_WIDTH == 0)
		return (NULL);

	move(infos, (infos->coord - MAP_WIDTH) + 1);

	return (infos);
}

void	*moveLeftDown(tInfos* infos)
{
	if ((infos->coord + MAP_WIDTH) - 1 < 0 \
		|| (infos->coord + MAP_WIDTH) - 1 >= getStrLen(infos->realMap) \
		|| infos->coord % MAP_WIDTH == 0)
		return (NULL);

	move(infos, (infos->coord + MAP_WIDTH) - 1);

	return (infos);
}

void	*moveRightDown(tInfos* infos)
{
	if ((infos->coord + MAP_WIDTH) + 1 < 0 \
		|| (infos->coord + MAP_WIDTH) + 1 >= getStrLen(infos->realMap) \
		|| (infos->coord + 1) % MAP_WIDTH == 0)
		return (NULL);

	move(infos, (infos->coord + MAP_WIDTH) + 1);

	return (infos);
}

void	moveRandomly(tInfos* infos)
{
	int	value = rand() % 8;

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

void	moveToTarget(tInfos* infos, const int target)
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

	else
		moveRandomly(infos);
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

		sendTargetInfo(infos, target);
		moveToTarget(infos, target);
	}
	else
		moveRandomly(infos);
}
