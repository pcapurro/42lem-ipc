#ifndef HEADER_H
# define HEADER_H

# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <stdio.h>

# include <semaphore.h>
# include <errno.h>
# include <sys/mman.h>
# include <fcntl.h>
# include <string.h>
# include <signal.h>

# include <sys/ipc.h>
# include <sys/msg.h>
# include <sys/shm.h>
# include <sys/types.h>
# include <sys/syscall.h>

# define SYSTEM_FAILED "Error! System failed."
# define MEMORY_FAILED "Error! Memory failed."

# define GAME_NAME "/game"
# define MSG_KEY 21000

struct sInfos
{
	int		mapFd;
	int		team;

	bool	init;

	int		msgId;
	char*	map;

	int		coord;
	bool	alive;
};

typedef struct sInfos tInfos;

struct sMessage
{
	long	teamId;
	int		info;
};

typedef struct sMessage tMsg;

int		getStrLen(const char* str);
void	writeStr(const char* str, const int fd);
bool	isDigit(const char nb);

void	order(tInfos* infos);
void	executeOrder(tInfos* infos, const char target);
void	moveNow(tInfos* infos);
void	dieNow(tInfos* infos);
void	move(tInfos* infos);

void	printMap(tInfos* infos);

void	startRoutine(tInfos* infos);
void	initializeRoutine(tInfos* infos, const char* arg);

void	loadMap(tInfos* infos);
void	initializeMap(tInfos* infos);

void	loadMessages(tInfos* infos);
void	initializeMessages(tInfos* infos);

void	systemFailed(void);
void	memoryFailed(void);

void	printHelp(void);
bool	isHelp(const char* str);

void	setToNull(tInfos* infos);
void	endFree(tInfos* infos);

int		main(const int argc, const char** arg);

#endif