#include "../../include/header.h"

int	createNewTarget(tInfos* infos)
{
	int	newTarget = -1;
	int	value = rand() % 2;

	if (value == 0)
	{
		for (int i = 0; infos->realMap[i] != '\0'; i++)
		{
			if (infos->realMap[i] > 48 && infos->realMap[i] != (infos->team + 48))
				{ newTarget = i; break ; }
		}
	}

	if (value == 1)
	{
		for (int i = getStrLen(infos->realMap) - 1; i != -1; i--)
		{
			if (infos->realMap[i] > 48 && infos->realMap[i] != (infos->team + 48))
				{ newTarget = i; break ; }
		}
	}

	printf("getting new target...\n");
	printf("new target : %d\n", newTarget);

	return (newTarget);
}

int		retrieveLastTarget(tInfos* infos)
{
	if (infos->lastTarget == -1)
		return (-1);

	int	mapLen = getStrLen(infos->realMap);

	int left = infos->lastTarget - 1;
	int right = infos->lastTarget + 1;

	int up = infos->lastTarget - MAP_WIDTH;
	int down = infos->lastTarget + MAP_WIDTH;

	int leftUp = up - 1;
	int leftDown = down - 1;

	int rightUp = up + 1;
	int rightDown = down + 1;

	if (left >= 0 && infos->realMap[left] > 48 && infos->realMap[left] != infos->team)
		return (left);

	if (right < mapLen && infos->realMap[right] > 48 && infos->realMap[right] != infos->team)
		return (right);

	if (up >= 0 && infos->realMap[up] > 48 && infos->realMap[up] != infos->team)
		return (up);

	if (down < mapLen && infos->realMap[down] > 48 && infos->realMap[down] != infos->team)
		return (down);

	if (leftUp >= 0 && leftUp < mapLen && infos->realMap[leftUp] > 48 \
		&& infos->realMap[leftUp] != infos->team)
		return (leftUp);

	if (leftDown >= 0 && leftDown < mapLen && infos->realMap[leftDown] > 48 \
		&& infos->realMap[leftDown] != infos->team)
		return (leftDown);

	if (rightUp >= 0 && rightUp < mapLen && infos->realMap[rightUp] > 48 \
		&& infos->realMap[rightUp] != infos->team)
		return (rightUp);

	if (rightDown >= 0 && rightDown < mapLen && infos->realMap[rightDown] > 48 \
		&& infos->realMap[rightDown] != infos->team)
		return (rightDown);

	return (-1);
}

int	getLastTarget(tInfos* infos)
{
	tMsg	message;

	printf("getting last target...\n");

	if (msgrcv(infos->msgId, &message, sizeof(message) - sizeof(long), infos->team, IPC_NOWAIT) == -1)
	{
		if (errno != EAGAIN && errno != EWOULDBLOCK && errno != ENOMSG)
			perror("42lem-ipc"), endFree(infos), exit(1);
		message.info = -1;
	}

	printf("last target: %d\n", message.info);

	return (message.info);
}

void	sendNewTarget(tInfos* infos, const int newTarget)
{
	tMsg	message;

	memset(&message, 0, sizeof(message));

	message.teamId = infos->team;
	message.info = newTarget;

	printf("sending new target to allies: %d\n", newTarget);

	if (msgsnd(infos->msgId, &message, sizeof(message) - sizeof(long), 0) == -1)
		perror("42lem-ipc"), endFree(infos), exit(1);
}
