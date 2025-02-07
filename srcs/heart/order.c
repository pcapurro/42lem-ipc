#include "../../include/header.h"

void	createOrder(tInfos* infos)
{
	int	newDest = -1;
	int	value = rand() % 2;

	if (value == 0)
	{
		for (int i = 0; infos->realMap[i] != '\0'; i++)
		{
			if (infos->realMap[i] > 48 && infos->realMap[i] != (infos->team + 48))
				{ newDest = i; break ; }
		}
	}

	if (value == 1)
	{
		for (int i = getStrLen(infos->realMap) - 1; i != -1; i--)
		{
			if (infos->realMap[i] > 48 && infos->realMap[i] != (infos->team + 48))
				{ newDest = i; break ; }
		}
	}

	infos->dest = newDest;
}

void	executeOrder(tInfos* infos, const char target)
{
	;
}
