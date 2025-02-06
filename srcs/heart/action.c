#include "../../include/header.h"

void	spawnNow(tInfos* infos)
{
	printf("spawning...\n");

	int	free = 0, value = 0;

	for (int i = 0; infos->realMap[i] != '\0'; i++)
	{
		if (infos->realMap[i] == '0')
			free++;
	}

	value = rand() % free - 1;
	free = 0;

	printf("%d\n", value);

	for (int i = 0; infos->realMap[i] != '\0'; i++)
	{
		if (infos->realMap[i] == '0')
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
	infos->realMap[infos->coord] = infos->team + 48;

	printf("'%d'\n", infos->coord);
}
