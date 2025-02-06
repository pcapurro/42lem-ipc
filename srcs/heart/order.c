#include "../../include/header.h"

void	createOrder(tInfos* infos)
{
	tMsg	data;

	int		newDest = -1;
	int		value = rand() % MAP_LENGTH;

	for (int i = value; i != 0; i--)
	{
		if (infos->realMap[i] > 48 && infos->realMap[i] != (infos->team + 48))
			newDest = i;
	}

	if (newDest == -1)
	{
		for (int i = 0; infos->realMap[i] != '\0'; i++)
		{
			if (infos->realMap[i] > 48 && infos->realMap[i] != (infos->team + 48))
				newDest = i;
		}
	}

	printf("> %d\n", newDest);

	printf("no order received: suggestion to attack map[%d] {x=%d ; y=%d} (team %c)\n", newDest, \
		newDest / MAP_WIDTH, newDest % MAP_WIDTH, infos->realMap[newDest]);
	infos->dest = newDest;
}

void	executeOrder(tInfos* infos, const char target)
{
	// printf("executing new createOrder\n");
}
