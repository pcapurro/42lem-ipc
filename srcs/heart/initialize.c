#include "../../include/header.h"

void	initializeMap(tInfos* infos)
{
	printf("initializing map...\n");

	infos->init = true;

	if (ftruncate(infos->mapFd, (sizeof(char) * 96)) != 0)
		perror("42lem-ipc: "), endFree(infos), exit(1);

	infos->map = mmap(NULL, sizeof(char) * 96, PROT_READ | PROT_WRITE, MAP_SHARED, infos->mapFd, 0);
	if (infos->map == MAP_FAILED)
		perror("42lem-ipc: "), endFree(infos), exit(1);

	infos->map[95] = '\0';
	for (int i = 0; i != 96; i++)
		infos->map[i] = '0';
}

void	initializeMessages(tInfos* infos)
{
	printf("initializing messages...\n");

	infos->init = true;

	infos->msgId = msgget(MSG_KEY, IPC_CREAT | 0666);
	if (infos->msgId == -1)
		perror("42lem-ipc: "), endFree(infos), exit(1);
}

void	initializeRoutine(tInfos* infos, const char* arg)
{
	infos->team = arg[0] - 48;

	infos->mapFd = shm_open(GAME_NAME, O_CREAT | O_EXCL | O_RDWR, 0666);
	if (infos->mapFd == -1)
	{
		if (errno != EEXIST)
			perror("42lem-ipc: "), endFree(infos), exit(1);

		infos->init = false;
		loadMap(infos);
		loadMessages(infos);
	}
	else
		initializeMap(infos), initializeMessages(infos);

	// infos->map[infos->team] = 'v';
}
