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

void	moveRandomly(tInfos* infos)
{
	int	value = rand() % 8;

	printf("moving randomly\n");

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
	if (infos->teamsNb == 1 || infos->alliesNb <= 1)
		{ moveRandomly(infos); return ; }

	tMsg	message;

	if (msgrcv(infos->msgId, &message, sizeof(message) - sizeof(long), infos->team, IPC_NOWAIT) == -1)
	{
		if (errno != EAGAIN && errno != EWOULDBLOCK && errno != ENOMSG)
			perror("42lem-ipc"), endFree(infos), exit(1);
		message.info = -1;
	}
	infos->dest = message.info;

	if (infos->dest == -1 || infos->realMap[infos->dest] == '0')
	{
		createOrder(infos);
		if (infos->dest != -1)
			printf("no order received: suggestion to attack map[%d] {x=%d ; y=%d} (team %c)\n", infos->dest, infos->dest / MAP_WIDTH, infos->dest % MAP_WIDTH, infos->realMap[infos->dest]);
	}
	else
		printf("order received to attack %d\n", infos->dest);

	if (infos->dest != -1)
	{
		memset(&message, 0, sizeof(message));

		message.teamId = infos->team;
		message.info = infos->dest;

		printf("%d ; %d\n", message.info, infos->dest);

		if (msgsnd(infos->msgId, &message, sizeof(message) - sizeof(long), 0) == -1)
			perror("42lem-ipc"), endFree(infos), exit(1);
		executeOrder(infos, message.info);
	}
}
