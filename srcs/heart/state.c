#include "../../include/header.h"

bool	isNowDead(tInfos* infos)
{
	int	attackers = 0;
	int	value = 0;
	int	mapLen = getStrLen(infos->realMap);

	value = infos->coord - 1;
	if (infos->coord >= 0 && infos->realMap[value] > 48 && infos->realMap[value] != infos->team)
		attackers++;

	value = infos->coord + 1;
	if (infos->realMap[value] > 48 && infos->realMap[value] != infos->team)
		attackers++;

	value = infos->coord - MAP_WIDTH;
	if (value >= 0 && infos->realMap[value] > 48 && infos->realMap[value] != infos->team)
		attackers++;

	value = infos->coord + MAP_WIDTH;
	if (value < mapLen && infos->realMap[value] > 48 && infos->realMap[value] != infos->team)
		attackers++;

	value = infos->coord - MAP_WIDTH - 1;
	if (value >= 0 && infos->realMap[value] > 48 && infos->realMap[value] != infos->team)
		attackers++;

	value = (infos->coord - MAP_WIDTH) + 1;
	if (value >= 0 && value < mapLen && infos->realMap[value] > 48 && infos->realMap[value] != infos->team)
		attackers++;

	value = infos->coord + MAP_WIDTH - 1;
	if (value >= 0 && infos->realMap[value] > 48 && infos->realMap[value] != infos->team)
		attackers++;

	value = infos->coord + MAP_WIDTH + 1;
	if (value < mapLen && infos->realMap[value] > 48 && infos->realMap[value] != infos->team)
		attackers++;

	if (attackers > 1)
		return (true);

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

int	getTeamsNumber(char** map)
{
	int		nb = 0;
	int		team = 0;

	for (int i = 0; map[i] != NULL; i++)
	{
		for (int k = 0; map[i][k] != '\0'; k++)
		{
			if (map[i][k] != '0')
			{
				team = map[i][k];
				removeElement(map, team);
				nb++;
			}
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
			infos->realMap[0] = '#';
			return (true);
		}
	}

	return (false);
}
