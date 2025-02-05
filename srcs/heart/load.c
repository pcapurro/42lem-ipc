#include "../../include/header.h"

void	loadMessages(tInfos* infos)
{
	printf("loading messages...\n");

	infos->init = false;

	infos->msgId = msgget(MSG_KEY, 0666);
	if (infos->msgId == -1)
		perror("42lem-ipc: "), endFree(infos), exit(1);
}

void	loadMap(tInfos* infos)
{
	printf("loading map...\n");

	infos->init = false;

	infos->mapFd = shm_open(GAME_NAME, O_RDWR, 0666);
	if (infos->mapFd == -1)
		perror("42lem-ipc: "), endFree(infos), exit(1);

	infos->map = mmap(NULL, sizeof(char) * 96, PROT_READ | PROT_WRITE, MAP_SHARED, infos->mapFd, 0);
	if (infos->map == MAP_FAILED)
		perror("42lem-ipc: "), endFree(infos), exit(1);
}
