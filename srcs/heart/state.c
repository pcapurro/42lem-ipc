#include "../../include/header.h"

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

void	getPlayersNumber(tInfos* infos)
{
	int	nb = 0;

	for (int i = 0; infos->realMap[i] != '\0'; i++)
	{
		if (infos->realMap[i] != '0' && infos->realMap[i] != '#')
			nb++;
	}
	infos->playersNb = nb;
}

void	removeTeam(tInfos* infos, const char team)
{
	for (int i = 0; infos->map[i] != NULL; i++)
	{
		for (int k = 0; infos->map[i][k] != '\0'; k++)
		{
			if (infos->map[i][k] == team)
				infos->map[i][k] = '0';
		}
	}
}

void	getTeamsNumber(tInfos* infos)
{
	int		nb = 0;
	char	team = '\0';

	for (int i = 0; infos->map[i] != NULL; i++)
	{
		for (int k = 0; infos->map[i][k] != '\0'; k++)
		{
			if (infos->map[i][k] != '0')
			{
				team = infos->map[i][k];
				removeTeam(infos, team);
				nb++;
			}
		}
	}

	infos->teamsNb = nb;
	if (infos->init == true)
	{
		if (infos->teamsNb > 1 && infos->state == false)
			infos->state = true;
	}
}

bool	isOver(tInfos* infos)
{
	bool	dead = false;

	if (isNowDead(infos) == true)
		dead = true;

	if (infos->init == false)
	{
		if (dead == true)
			return (true);

		for (int i = 0; infos->realMap[i] != '\0'; i++)
		{
			if (infos->realMap[i] == '#')
				return (true);
		}
	}
	else
	{
		if (dead == true)
		{
			infos->realMap[infos->coord] = '0';
			infos->coord = -1;
		}

		if (infos->state == true && infos->teamsNb == 1)
		{
			infos->realMap[infos->coord] = '#';
			return (true);
		}
	}

	return (false);
}
