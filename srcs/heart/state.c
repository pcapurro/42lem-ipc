#include "../../include/header.h"

bool	isNowDead(tInfos* infos)
{
	int	attackers[8];
	int	value = 0;
	int	mapLen = getStrLen(infos->map);

	for (int i = 0; i != 8; i++)
		attackers[i] = '0';

	value = infos->coord - 1;
	if (infos->coord % MAP_WIDTH != 0)
	{
		if (infos->map[value] > 48 && infos->map[value] != infos->team + 48)
			attackers[0] = infos->map[value];
	}

	value = infos->coord + 1;
	if (value % MAP_WIDTH != 0)
	{
		if (infos->map[value] > 48 && infos->map[value] != infos->team + 48)
			attackers[1] = infos->map[value];
	}

	value = infos->coord - MAP_WIDTH;
	if (value >= 0 && infos->map[value] > 48 && infos->map[value] != infos->team + 48)
		attackers[2] = infos->map[value];

	value = infos->coord + MAP_WIDTH;
	if (value < mapLen && infos->map[value] > 48 && infos->map[value] != infos->team + 48)
		attackers[3] = infos->map[value];


	value = infos->coord - MAP_WIDTH - 1;
	if (infos->coord % MAP_WIDTH != 0)
	{
		if (value >= 0 && infos->map[value] > 48 && infos->map[value] != infos->team + 48)
			attackers[4] = infos->map[value];
	}

	value = (infos->coord - MAP_WIDTH) + 1;
	if ((infos->coord + 1) % MAP_WIDTH != 0)
	{
		if (value >= 0 && value < mapLen && infos->map[value] > 48 && infos->map[value] != infos->team + 48)
			attackers[5] = infos->map[value];
	}

	value = infos->coord + MAP_WIDTH - 1;
	if (infos->coord % MAP_WIDTH != 0)
	{
		if (value >= 0 && infos->map[value] > 48 && infos->map[value] != infos->team + 48)
			attackers[6] = infos->map[value];
	}

	value = infos->coord + MAP_WIDTH + 1;
	if ((infos->coord + 1) % MAP_WIDTH != 0)
	{
		if (value < mapLen && infos->map[value] > 48 && infos->map[value] != infos->team + 48)
			attackers[7] = infos->map[value];
	}

	for (int i = 0; i != 8; i++)
	{
		if (attackers[i] <= 48 || attackers[i] == infos->team + 48)
			continue ;

		for (int k = 0; k != 8; k++)
		{
			if (k != i && attackers[k] == attackers[i] && attackers[k] != infos->team + 48)
				return (true);
		}
	}

	return (false);
}

int	getPlayersNumber(tInfos* infos)
{
	int	nb = 0;

	for (int i = 0; infos->map[i] != '\0'; i++)
	{
		if (infos->map[i] > 48)
			nb++;
	}
	
	return (nb);
}

int	getAlliesNumber(tInfos* infos)
{
	int	nb = 0;

	for (int i = 0; infos->map[i] != '\0'; i++)
	{
		if (infos->map[i] == infos->team + 48)
			nb++;
	}
	
	return (nb);
}

int	getTeamsNumber(tInfos* infos)
{
	int	nb = 0;

	for (int k = 1; k != 10; k++)
	{
		for (int i = 0; infos->map[i] != '\0'; i++)
		{
			if (infos->map[i] != '0' && infos->map[i] - 48 == k)
				{ nb++; break ; }
		}
	}

	return (nb);
}

bool	isOver(tInfos* infos)
{
	bool	dead = false;

	if (infos->coord != -1 && isNowDead(infos) == true)
		dead = true;

	if (infos->init == false)
	{
		if (dead == true)
			return (true);

		for (int i = 0; infos->map[i] != '\0'; i++)
		{
			if (infos->map[i] == '#')
				return (true);
		}
	}
	else
	{
		if (dead == true)
		{
			infos->map[infos->coord] = '0';
			infos->coord = -1;
		}

		if (infos->state == true && infos->teamsNb == 1)
		{
			for (int i = 0; infos->map[i] != '\0'; i++)
				infos->map[i] = '#';
			return (true);
		}
	}

	return (false);
}
