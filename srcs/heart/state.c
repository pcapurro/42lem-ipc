#include "../../include/header.h"

bool	isNowDead(tInfos* infos)
{
	int	attackers[8];
	int	value = 0;
	int	mapLen = getStrLen(infos->realMap);

	for (int i = 0; i != 8; i++)
		attackers[i] = '0';

	value = infos->coord - 1;
	if (infos->coord % MAP_WIDTH != 0)
	{
		if (infos->realMap[value] > 48 && infos->realMap[value] != infos->team + 48)
			attackers[0] = infos->realMap[value];
	}

	value = infos->coord + 1;
	if (value % MAP_WIDTH != 0)
	{
		if (infos->realMap[value] > 48 && infos->realMap[value] != infos->team + 48)
			attackers[1] = infos->realMap[value];
	}

	value = infos->coord - MAP_WIDTH;
	if (value >= 0 && infos->realMap[value] > 48 && infos->realMap[value] != infos->team + 48)
		attackers[2] = infos->realMap[value];

	value = infos->coord + MAP_WIDTH;
	if (value < mapLen && infos->realMap[value] > 48 && infos->realMap[value] != infos->team + 48)
		attackers[3] = infos->realMap[value];


	value = infos->coord - MAP_WIDTH - 1;
	if (infos->coord % MAP_WIDTH != 0)
	{
		if (value >= 0 && infos->realMap[value] > 48 && infos->realMap[value] != infos->team + 48)
			attackers[4] = infos->realMap[value];
	}

	value = (infos->coord - MAP_WIDTH) + 1;
	if ((infos->coord + 1) % MAP_WIDTH != 0)
	{
		if (value >= 0 && value < mapLen && infos->realMap[value] > 48 && infos->realMap[value] != infos->team + 48)
			attackers[5] = infos->realMap[value];
	}

	value = infos->coord + MAP_WIDTH - 1;
	if (infos->coord % MAP_WIDTH != 0)
	{
		if (value >= 0 && infos->realMap[value] > 48 && infos->realMap[value] != infos->team + 48)
			attackers[6] = infos->realMap[value];
	}

	value = infos->coord + MAP_WIDTH + 1;
	if ((infos->coord + 1) % MAP_WIDTH != 0)
	{
		if (value < mapLen && infos->realMap[value] > 48 && infos->realMap[value] != infos->team + 48)
			attackers[7] = infos->realMap[value];
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

int	getPlayersNumber(const char* map)
{
	int	nb = 0;

	for (int i = 0; map[i] != '\0'; i++)
	{
		if (map[i] > 48)
			nb++;
	}
	
	return (nb);
}

int	getAlliesNumber(const char* map, const int team)
{
	int	nb = 0;

	for (int i = 0; map[i] != '\0'; i++)
	{
		if (map[i] == team + 48)
			nb++;
	}
	
	return (nb);
}

int	getTeamsNumber(char* map)
{
	int	nb = 0;

	for (int k = 1; k != 10; k++)
	{
		for (int i = 0; map[i] != '\0'; i++)
		{
			if (map[i] != '0' && map[i] - 48 == k)
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
			for (int i = 0; infos->realMap[i] != '\0'; i++)
				infos->realMap[i] = '#';
			return (true);
		}
	}

	return (false);
}
