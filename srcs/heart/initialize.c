#include "../../include/header.h"

void	initializeMap(tInfos* infos)
{
	if (infos->init == true)
	{
		if (ftruncate(infos->mapFd, sizeof(char) * (MAP_LENGTH + 1)) != 0)
			perror("42lem-ipc"), endFree(infos, 1);
	}
	else
		infos->mapFd = shm_open(GAME_NAME, O_RDWR, 0666);

	if (infos->mapFd == -1)
		perror("42lem-ipc"), endFree(infos, 1);

	infos->map = mmap(NULL, sizeof(char) * (MAP_LENGTH + 1), \
		PROT_READ | PROT_WRITE, MAP_SHARED, infos->mapFd, 0);

	if (infos->map == MAP_FAILED)
		perror("42lem-ipc"), endFree(infos, 1);

	if (infos->init == true)
	{
		infos->map[MAP_LENGTH] = '\0';
		for (int i = 0; i != MAP_LENGTH; i++)
			infos->map[i] = '0';
	}
}

void	initializeMessages(tInfos* infos)
{
	if (infos->init == true)
		infos->msgId = msgget(MSG_KEY, IPC_CREAT | 0666);
	else
		infos->msgId = msgget(MSG_KEY, 0666);

	if (infos->msgId == -1)
		perror("42lem-ipc"), endFree(infos, 1);
}

void	initializeSemaphores(tInfos* infos)
{
	if (infos->init == true)
		infos->access = sem_open(ACC_NAME, O_CREAT, 0666, 1);
	else
		infos->access = sem_open(ACC_NAME, 0);

	if (infos->access == SEM_FAILED)
		perror("42lem-ipc"), endFree(infos, 1);
}

void	initializeRoutine(tInfos* infos, const char* arg)
{
	infos->mapFd = shm_open(GAME_NAME, O_CREAT | O_EXCL | O_RDWR, 0666);
	if (infos->mapFd == -1)
	{
		if (errno != EEXIST)
			perror("42lem-ipc"), endFree(infos, 1);
		infos->init = false;
	}
	else
		infos->init = true;

	infos->team = arg[0] - 48;

	initializeSemaphores(infos);
	initializeMap(infos);
	initializeMessages(infos);
}
