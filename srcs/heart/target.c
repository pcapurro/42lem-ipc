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
	int	newTarget = 0;

	printf("retrieving last target...\n");

	printf("last target: %d\n", newTarget);

	return (newTarget);
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
