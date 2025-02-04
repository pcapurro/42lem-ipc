#include "../../include/header.h"

void	initializeMap(tInfos* infos)
{
	printf("initializing map...\n");

	infos->init = true;

	if (ftruncate(infos->fd, (sizeof(char) * 96)) != 0)
		perror("42lem-ipc: "), endFree(infos), exit(1);

	infos->map = mmap(NULL, sizeof(char) * 96, PROT_READ | PROT_WRITE, MAP_SHARED, infos->fd, 0);
	if (infos->map == MAP_FAILED)
		perror("42lem-ipc: "), endFree(infos), exit(1);

	infos->map[95] = '\0';
	for (int i = 0; i != 96; i++)
		infos->map[i] = '0';
}

void	loadMap(tInfos* infos)
{
	printf("loading map...\n");

	infos->init = false;

	infos->fd = shm_open("/game", O_RDWR, 0666);
	if (infos->fd == -1)
		perror("42lem-ipc: "), endFree(infos), exit(1);

	infos->map = mmap(NULL, sizeof(char) * 96, PROT_READ | PROT_WRITE, MAP_SHARED, infos->fd, 0);
	if (infos->map == MAP_FAILED)
		perror("42lem-ipc: "), endFree(infos), exit(1);
}

void	initializeRoutine(tInfos* infos, const char* arg)
{
	infos->fd = shm_open("/game", O_CREAT | O_EXCL | O_RDWR, 0666);
	if (infos->fd == -1)
	{
		if (errno != EEXIST)
			perror("42lem-ipc: "), endFree(infos), exit(1);
		loadMap(infos);
	}
	else
		initializeMap(infos);

	infos->team = arg[0] - 48;
	// infos->map[infos->team] = 'v';
}
