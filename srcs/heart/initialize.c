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

	infos->msgFd = shm_open("/messages", O_CREAT | O_EXCL | O_RDWR, 0666);
	if (infos->msgFd == -1)
		perror("42lem-ipc: "), endFree(infos), exit(1);

	if (ftruncate(infos->msgFd, (sizeof(key_t) * 10)) != 0)
		perror("42lem-ipc: "), endFree(infos), exit(1);

	infos->messages = mmap(NULL, sizeof(key_t) * 10, PROT_READ | PROT_WRITE, MAP_SHARED, infos->msgFd, 0);
	if (infos->messages == MAP_FAILED)
		perror("42lem-ipc: "), endFree(infos), exit(1);

	for (int i = 0, value = 21000; i != 10; i++, value++)
	{
		infos->messages[i] = msgget(value, 0666 | IPC_CREAT);
		if (infos->messages[i] == -1)
			perror("42lem-ipc: "), endFree(infos), exit(1);
		// else
			// printf("%d : '%d'\n", i, infos->messages[i]);
	}

	// tMsg	message;
	// message.type = 1;
	// message.message = strdup("wsh");
	// msgsnd(infos->messages[3], &message, sizeof(message.message), 0);
	// printf("wrote message '%s' at %d\n", message.message, infos->messages[3]);
	// sleep(5);
}

void	initializeRoutine(tInfos* infos, const char* arg)
{
	infos->team = arg[0] - 48;

	infos->mapFd = shm_open("/game", O_CREAT | O_EXCL | O_RDWR, 0666);
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
