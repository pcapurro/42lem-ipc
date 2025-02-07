#include "../../include/header.h"

int	spawnNow(tInfos* infos)
{
	int	free = 0, value = 0;

	for (int i = 0; infos->realMap[i] != '\0'; i++)
	{
		if (infos->realMap[i] == '0')
			free++;
	}

	if (free == 0)
	{
		writeStr("Error! Could not join the game (map is full)\n", 2);
		endFree(infos);
		exit(1);
	}

	value = rand() % free;
	free = 0;

	for (int i = 0; infos->realMap[i] != '\0'; i++)
	{
		if (infos->realMap[i] == '0')
		{
			free++;
			if (free == value)
				infos->coord = i;
		}
	}
	infos->realMap[infos->coord] = infos->team + 48;

	return (0);
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

void	moveNow(tInfos* infos)
{
	// if (infos->teamsNb == 1)
		moveRandomly(infos);
	// else
	// {
	// 	tMsg	data;

	// 	if (msgrcv(infos->msgId, &data, sizeof(data) - sizeof(long), infos->team, IPC_NOWAIT) == -1)
	// 	{
	// 		if (errno != EAGAIN && errno != EWOULDBLOCK && errno != ENOMSG)
	// 			perror("42lem-ipc"), endFree(infos), exit(1);
	// 		data.info = -1;
	// 	}
	// 	infos->dest = data.info;

	// 	if (infos->dest == -1 || infos->realMap[infos->dest] == '0')
	// 		createOrder(infos);

	// 	if (infos->dest == -1)
	// 		return ;

	// 	data.info = infos->dest;
	// 	data.teamId = infos->team;

	// 	if (msgsnd(infos->msgId, &data, sizeof(data) - sizeof(long), 0) == -1)
	// 		perror("42lem-ipc"), endFree(infos), exit(1);
	// 	executeOrder(infos, data.info);
	// }

	// infos->realMap[infos->coord] = infos->team + 48;
}
