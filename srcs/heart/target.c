#include "../../include/header.h"

int	createNewTarget(tInfos* infos)
{
	int	newTarget = -1;
	int	value = rand() % 2;

	if (value == 0)
	{
		for (int i = 0; infos->realMap[i] != '\0'; i++)
		{
			if (infos->realMap[i] > 48 && infos->realMap[i] != infos->team + 48)
				{ newTarget = i; break ; }
		}
	}

	if (value == 1)
	{
		for (int i = getStrLen(infos->realMap) - 1; i != -1; i--)
		{
			if (infos->realMap[i] > 48 && infos->realMap[i] != infos->team + 48)
				{ newTarget = i; break ; }
		}
	}

	// printf("getting new target...\n");
	// printf("new target : %c%d\n", "abcdefghijklmnopqrstu"[newTarget % MAP_WIDTH], newTarget / MAP_WIDTH);

	return (newTarget);
}

int		retrieveLastTarget(tInfos* infos)
{
	if (infos->lastTarget == -1)
		return (-1);

	int	mapLen = getStrLen(infos->realMap);

	// printf("target last coord : %c%d\n", "abcdefghijklmnopqrstuvalue"[infos->lastTarget % MAP_WIDTH], infos->lastTarget / MAP_WIDTH);

	for (int i = 1, value = 0; i != 2; i++)
	{
		value = infos->lastTarget - i;
		// printf("checking %c%d\n", "abcdefghijklmnopqrstuvalue"[value % MAP_WIDTH], value / MAP_WIDTH);
		if (infos->lastTarget >= 0 && infos->realMap[value] > 48 && infos->realMap[value] != infos->team + 48)
			return (value);

		value = infos->lastTarget + i;
		// printf("checking %c%d\n", "abcdefghijklmnopqrstu"[value % MAP_WIDTH], value / MAP_WIDTH);
		if (infos->realMap[value] > 48 && infos->realMap[value] != infos->team + 48)
			return (value);

		value = infos->lastTarget - (MAP_WIDTH * i);
		// printf("checking %c%d\n", "abcdefghijklmnopqrstu"[value % MAP_WIDTH], value / MAP_WIDTH);
		if (value >= 0 && infos->realMap[value] > 48 && infos->realMap[value] != infos->team + 48)
			return (value);

		value = infos->lastTarget + (MAP_WIDTH * i);
		// printf("checking %c%d\n", "abcdefghijklmnopqrstu"[value % MAP_WIDTH], value / MAP_WIDTH);
		if (value < mapLen && infos->realMap[value] > 48 && infos->realMap[value] != infos->team + 48)
			return (value);

		value = infos->lastTarget - (MAP_WIDTH * i) - i;
		// printf("checking %c%d\n", "abcdefghijklmnopqrstu"[value % MAP_WIDTH], value / MAP_WIDTH);
		if (value >= 0 && infos->realMap[value] > 48 && infos->realMap[value] != infos->team + 48)
			return (value);

		value = (infos->lastTarget - (MAP_WIDTH * i)) + i;
		// printf("checking %c%d\n", "abcdefghijklmnopqrstu"[value % MAP_WIDTH], value / MAP_WIDTH);
		if (value >= 0 && value < mapLen && infos->realMap[value] > 48 && infos->realMap[value] != infos->team + 48)
			return (value);

		value = infos->lastTarget + (MAP_WIDTH * i) - i;
		// printf("checking %c%d\n", "abcdefghijklmnopqrstu"[value % MAP_WIDTH], value / MAP_WIDTH);
		if (value >= 0 && infos->realMap[value] > 48 && infos->realMap[value] != infos->team + 48)
			return (value);

		value = infos->lastTarget + (MAP_WIDTH * i) + i;
		// printf("checking %c%d\n", "abcdefghijklmnopqrstu"[value % MAP_WIDTH], value / MAP_WIDTH);
		if (value < mapLen && infos->realMap[value] > 48 && infos->realMap[value] != infos->team + 48)
			return (value);
	}

	return (-1);
}

int	getLastTarget(tInfos* infos)
{
	tMsg	message;

	// printf("getting last target...\n");

	if (msgrcv(infos->msgId, &message, sizeof(message) - sizeof(long), infos->team, IPC_NOWAIT) == -1)
	{
		if (errno != EAGAIN && errno != EWOULDBLOCK && errno != ENOMSG)
			perror("42lem-ipc"), endFree(infos), exit(1);
		message.info = -1;
	}

	// printf("last target: %c%d\n", "abcdefghijklmnopqrstu"[message.info % MAP_WIDTH], message.info / MAP_WIDTH);

	return (message.info);
}

void	sendTargetInfo(tInfos* infos, const int newTarget)
{
	tMsg	message;

	memset(&message, 0, sizeof(message));

	message.teamId = infos->team;
	message.info = newTarget;

	// printf("sending new target to allies : %c%d\n", "abcdefghijklmnopqrstu"[newTarget % MAP_WIDTH], newTarget / MAP_WIDTH);

	if (msgsnd(infos->msgId, &message, sizeof(message) - sizeof(long), 0) == -1)
		perror("42lem-ipc"), endFree(infos), exit(1);
}
