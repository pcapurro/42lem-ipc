#include "../../include/header.h"

int	createNewTarget(tInfos* infos)
{
	int	newTarget = -1;
	int	value = 0;
	
	srand(time(NULL));
	value = rand() % 2;

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

	return (newTarget);
}

int		retrieveTarget(tInfos* infos, const int target)
{
	int	mapLen = getStrLen(infos->realMap);
	int	value = 0;

	value = target - 1;
	if (target != 0 && target % MAP_WIDTH != 0 \
		&& infos->realMap[value] > 48 && infos->realMap[value] != infos->team + 48)
		return (value);

	value = target + 1;
	if (value % MAP_WIDTH != 0 && value < mapLen \
		&& infos->realMap[value] > 48 && infos->realMap[value] != infos->team + 48)
		return (value);

	value = target - MAP_WIDTH;
	if (value >= 0 && infos->realMap[value] > 48 && infos->realMap[value] != infos->team + 48)
		return (value);

	value = target + MAP_WIDTH;
	if (value < mapLen && infos->realMap[value] > 48 && infos->realMap[value] != infos->team + 48)
		return (value);


	value = target - MAP_WIDTH - 1;
	if (value >= 0 && target % MAP_WIDTH != 0 \
		&& infos->realMap[value] > 48 && infos->realMap[value] != infos->team + 48)
		return (value);

	value = (target - MAP_WIDTH) + 1;
	if (value >= 0 && value < mapLen && (target + 1) % MAP_WIDTH != 0 \
		&& infos->realMap[value] > 48 && infos->realMap[value] != infos->team + 48)
		return (value);

	value = (target + MAP_WIDTH) - 1;
	if (value >= 0 && value < mapLen && target % MAP_WIDTH != 0 \
		&& infos->realMap[value] > 48 && infos->realMap[value] != infos->team + 48)
		return (value);

	value = target + MAP_WIDTH + 1;
	if (value >= 0 && value < mapLen && (target + 1) % MAP_WIDTH != 0 \
		&& infos->realMap[value] > 48 && infos->realMap[value] != infos->team + 48)
		return (value);

	return (-1);
}

int		retrieveLastTarget(tInfos* infos, const int lastTarget)
{
	if (lastTarget == -1)
		return (-1);

	int	mapLen = getStrLen(infos->realMap);
	int target = -1;

	target = retrieveTarget(infos, lastTarget);

	if (target == -1 && lastTarget % MAP_WIDTH != 0)
		target = retrieveTarget(infos, lastTarget - 1);
	if (target == -1 && (lastTarget + 1) % MAP_WIDTH != 0)
		target = retrieveTarget(infos, lastTarget + 1);

	if (target == -1 && (lastTarget - MAP_WIDTH) >= 0)
		target = retrieveTarget(infos, lastTarget - MAP_WIDTH);
	if (target == -1 && lastTarget + MAP_WIDTH < mapLen)
		target = retrieveTarget(infos, lastTarget + MAP_WIDTH);

	if (target == -1 && (lastTarget - MAP_WIDTH - 1) >= 0 \
		&& lastTarget % MAP_WIDTH != 0)
		target = retrieveTarget(infos, (lastTarget - MAP_WIDTH) - 1);
	if (target == -1 && ((lastTarget - MAP_WIDTH) + 1) >= 0 \
		&& (lastTarget + 1) % MAP_WIDTH != 0)
		target = retrieveTarget(infos, (lastTarget - MAP_WIDTH) + 1);

	if (target == -1 && (lastTarget + (MAP_WIDTH) - 1) < mapLen \
		&& lastTarget % MAP_WIDTH != 0)
		target = retrieveTarget(infos, (lastTarget + (MAP_WIDTH)) - 1);
	if (target == -1 && (lastTarget + (MAP_WIDTH) + 1) < mapLen \
		&& (lastTarget + 1) % MAP_WIDTH != 0)
		target = retrieveTarget(infos, (lastTarget + (MAP_WIDTH)) + 1);

	return (target);
}

int	getLastTarget(tInfos* infos)
{
	tMsg	message;

	if (msgrcv(infos->msgId, &message, sizeof(message) - sizeof(long), \
		infos->team, IPC_NOWAIT) == -1)
	{
		if (errno != EAGAIN && errno != EWOULDBLOCK && errno != ENOMSG)
			perror("42lem-ipc"), endFree(infos), exit(1);
		message.info = -1;
	}

	return (message.info);
}

void	sendTargetInfo(tInfos* infos)
{
	tMsg	message;
	void*	ptr = &message;

	for (int i = 0; i != sizeof(message); i++)
		((unsigned char*)ptr)[i] = 0;

	message.teamId = infos->team;
	message.info = infos->target;

	if (msgsnd(infos->msgId, &message, sizeof(message) - sizeof(long), 0) == -1)
		perror("42lem-ipc"), endFree(infos), exit(1);
}
