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
