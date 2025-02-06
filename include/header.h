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

# define ERASE_LINE "\033[1A\033[2K"

# define GAME_NAME "/game"
# define MSG_KEY 21000

# define MAP_WIDTH 21
# define MAP_HEIGHT 16
# define MAP_LENGTH (MAP_WIDTH * MAP_HEIGHT)

struct sInfos
{
	int		mapFd;
	int		team;

	bool	init;
	bool	state;

	int		dest;

	int		playersNb;
	int		teamsNb;

	int		msgId;
	char*	realMap;
	char**	map;

	int		coord;
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

void	createOrder(tInfos* infos);
void	executeOrder(tInfos* infos, const char target);
int		spawnNow(tInfos* infos);
void	moveNow(tInfos* infos);

bool	isOver(tInfos* infos);
bool	isNowDead(tInfos* infos);

void	getTeamsNumber(tInfos* infos);
void	getPlayersNumber(tInfos* infos);

void	updateMap(tInfos* infos);
void	printMap(tInfos* infos);

void	startRoutine(tInfos* infos);
void	initializeRoutine(tInfos* infos, const char* arg);

void	initializeMap(tInfos* infos);
void	initializeMessages(tInfos* infos);

void	systemFailed(void);
void	memoryFailed(void);

void	printHelp(void);
bool	isHelp(const char* str);

void	setToNull(tInfos* infos);
void	endFree(tInfos* infos);

int		main(const int argc, const char** arg);

#endif