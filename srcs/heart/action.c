#include "../../include/header.h"

void	spawnNow(tInfos* infos)
{
	printf("spawning...\n");

	int	free = 0, value = 0;

	for (int i = 0; infos->map[i] != '\0'; i++)
	{
		if (infos->map[i] == '0')
			free++;
	}

	value = rand() % free;
	free = 0;

	for (int i = 0; infos->map[i] != '\0'; i++)
	{
		if (infos->map[i] == '0')
		{
			free++;
			if (free == value)
				infos->coord = i;
		}
	}

	infos->alive = true;
}

void	moveNow(tInfos* infos)
{
	printf("moving now...\n");

	if (infos->coord == -1)
		spawnNow(infos);
	else
	{
		tMsg	data;

		if (msgrcv(infos->msgId, &data, sizeof(data) - sizeof(long), infos->team, IPC_NOWAIT) == -1)
		{
			if (errno != EAGAIN && errno != EWOULDBLOCK && errno != ENOMSG)
				perror("42lem-ipc: "), endFree(infos), exit(1);
			else
				order(infos);
		}
		else
			executeOrder(infos, data.info);
	}
	infos->map[infos->coord] = infos->team + 48;
}


void	dieNow(tInfos* infos)
{
	printf("dying now...\n");

	infos->alive = false;
}
