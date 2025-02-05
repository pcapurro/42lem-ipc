#include "../../include/header.h"

void	loadMessages(tInfos* infos)
{
	printf("loading messages...\n");

	infos->init = false;

	infos->msgFd = shm_open("/messages", O_RDWR, 0666);
	if (infos->msgFd == -1)
		perror("42lem-ipc: "), endFree(infos), exit(1);

	infos->messages = mmap(NULL, sizeof(int) * 10, PROT_READ | PROT_WRITE, MAP_SHARED, infos->msgFd, 0);
	if (infos->messages == MAP_FAILED)
		perror("42lem-ipc: "), endFree(infos), exit(1);

	// printf("%d\n", infos->team - 1);
	// printf("%d\n", infos->messages[infos->team - 1]);

	// tMsg	message;
	// int		id = infos->messages[infos->team - 1];
	// int		msgId = msgget(id, 0666);

	// perror(":");

	// printf("reading message at %d : '%d' (%d)\n", infos->team - 1, infos->messages[infos->team - 1], msgId);

	// msgrcv(msgId, &message, sizeof(message.message), 1, 0);
	// printf("> '%s'\n", message.message);
}

void	loadMap(tInfos* infos)
{
	printf("loading map...\n");

	infos->init = false;

	infos->mapFd = shm_open("/game", O_RDWR, 0666);
	if (infos->mapFd == -1)
		perror("42lem-ipc: "), endFree(infos), exit(1);

	infos->map = mmap(NULL, sizeof(char) * 96, PROT_READ | PROT_WRITE, MAP_SHARED, infos->mapFd, 0);
	if (infos->map == MAP_FAILED)
		perror("42lem-ipc: "), endFree(infos), exit(1);
}
