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
# include <time.h>
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
# define ACC_NAME "/access"
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

	int		target;

	int		playersNb;
	int		alliesNb;
	int		teamsNb;

	int		msgId;
	char*	map;

	int		coord;

	sem_t*	access;
};

typedef struct sInfos tInfos;

struct sMessage
{
	long	teamId;
	int		info;
};

typedef struct sMessage tMsg;

int		getStrLen(const char* str);
bool	isDigit(const char nb);
void	writeStr(const char* str, const int fd);

int		createNewTarget(tInfos* infos);
int		getLastTarget(tInfos* infos);

int		retrieveTarget(tInfos* infos, const int target);
int		retrieveLastTarget(tInfos* infos, const int lastTarget);

void	sendTargetInfo(tInfos* infos);

void	spawnNow(tInfos* infos);

void	move(tInfos* infos, const int newCoord);

void	*moveLeft(tInfos* infos);
void	*moveRight(tInfos* infos);
void	*moveUp(tInfos* infos);
void	*moveDown(tInfos* infos);

void	*moveLeftUp(tInfos* infos);
void	*moveRightUp(tInfos* infos);
void	*moveLeftDown(tInfos* infos);
void	*moveRightDown(tInfos* infos);

void	moveRandomly(tInfos* infos);
void	moveToTarget(tInfos* infos);
void	moveNow(tInfos* infos);

bool	isOver(tInfos* infos);
bool	isNowDead(tInfos* infos);

int		getTeamsNumber(tInfos* infos);
int		getAlliesNumber(tInfos* infos);
int		getPlayersNumber(tInfos* infos);
void	getGameInfos(tInfos* infos);

void	printColor(const int team);
void	printMap(tInfos* infos);

void	startRoutine(tInfos* infos);
void	initializeRoutine(tInfos* infos, const char* arg);

void	initializeSemaphores(tInfos* infos);
void	initializeMap(tInfos* infos);
void	initializeMessages(tInfos* infos);

void	systemFailed(void);
void	memoryFailed(void);

void	printHelp(void);
bool	isHelp(const char* str);

void	setToNull(tInfos* infos);
void	endFree(tInfos* infos, const int value);

int		main(const int argc, const char** arg);

#endif