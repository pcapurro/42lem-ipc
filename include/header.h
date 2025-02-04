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

# include <sys/ipc.h>
# include <sys/shm.h>
# include <sys/types.h>
# include <sys/syscall.h>

# define SYSTEM_FAILED "Error! System failed."
# define MEMORY_FAILED "Error! Memory failed."

struct sInfos
{
	int		fd;
	int		team;

	bool	init;

	char*	map;

};

typedef struct sInfos tInfos;

int		getStrLen(const char* str);
void	writeStr(const char* str, const int fd);
bool	isDigit(const char nb);

void	loadMap(tInfos* infos);
void	initializeMap(tInfos* infos);

void	startRoutine(tInfos* infos);
void	initializeRoutine(tInfos* infos, const char* arg);

void	systemFailed(void);
void	memoryFailed(void);

void	printHelp(void);
bool	isHelp(const char* str);

void	setToNull(tInfos* infos);
void	endFree(tInfos* infos);

int		main(const int argc, const char** arg);

#endif