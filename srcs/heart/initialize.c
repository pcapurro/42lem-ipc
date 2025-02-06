#include "../../include/header.h"

void	initializeMap(tInfos* infos)
{
	// if (infos->init == true)
	// 	printf("initializing map...\n");
	// else
	// 	printf("loading map...\n");

	if (infos->init == true)
	{
		if (ftruncate(infos->mapFd, sizeof(char) * (MAP_LENGTH + 1)) != 0)
			perror("42lem-ipc: "), endFree(infos), exit(1);
	}
	else
	{
		infos->mapFd = shm_open(GAME_NAME, O_RDWR, 0666);
		if (infos->mapFd == -1)
			perror("42lem-ipc: "), endFree(infos), exit(1);
	}

	infos->realMap = mmap(NULL, sizeof(char) * (MAP_LENGTH + 1), PROT_READ | PROT_WRITE, MAP_SHARED, infos->mapFd, 0);
	if (infos->realMap == MAP_FAILED)
		perror("42lem-ipc: "), endFree(infos), exit(1);
	
	if (infos->init == true)
	{
		infos->realMap[MAP_LENGTH] = '\0';
		for (int i = 0; i != MAP_LENGTH; i++)
			infos->realMap[i] = '0';
	}

	infos->map = malloc(sizeof(char*) * (MAP_HEIGHT + 1));
	if (!infos->map)
		memoryFailed(), endFree(infos), exit(1);
	for (int i = 0; i != MAP_HEIGHT; i++)
	{
		infos->map[i] = NULL;
		infos->map[i] = malloc(sizeof(char) * (MAP_WIDTH + 1));
		if (!infos->map[i])
			memoryFailed(), endFree(infos), exit(1);

		for (int k = 0; k != MAP_WIDTH; k++)
			infos->map[i][k] = '0';
		infos->map[i][MAP_WIDTH] = '\0';
	}
	infos->map[MAP_HEIGHT] = NULL;
}

void	initializeMessages(tInfos* infos)
{
	// if (infos->init == true)
	// 	printf("initializing messages...\n");
	// else
	// 	printf("loading messages...\n");

	if (infos->init == true)
		infos->msgId = msgget(MSG_KEY, IPC_CREAT | 0666);
	else
		infos->msgId = msgget(MSG_KEY, 0666);

	if (infos->msgId == -1)
		perror("42lem-ipc: "), endFree(infos), exit(1);
}

void	initializeRoutine(tInfos* infos, const char* arg)
{
	infos->mapFd = shm_open(GAME_NAME, O_CREAT | O_EXCL | O_RDWR, 0666);
	if (infos->mapFd == -1)
	{
		if (errno != EEXIST)
			perror("42lem-ipc: "), endFree(infos), exit(1);
		infos->init = false;
	}
	else
		infos->init = true;

	infos->team = arg[0] - 48;
	initializeMap(infos);
	initializeMessages(infos);
}
