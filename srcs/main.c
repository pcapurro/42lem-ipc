#include "../include/header.h"

tInfos*	data;

void	setToNull(tInfos* infos)
{
	infos->mapFd = -1;
	infos->team = 0;

	infos->init = false;
	infos->state = false;

	infos->target = -1;
	infos->lastTarget = -1;

	infos->playersNb = 1;
	infos->alliesNb = 1;
	infos->teamsNb = 1;

	infos->msgId = -1;
	infos->realMap = NULL;
	infos->map = NULL;

	infos->coord = -1;
}

void	endFree(tInfos* infos)
{
	if (infos->access != SEM_FAILED)
	{
		sem_close(infos->access);
		if (infos->init == true)
			sem_unlink(ACC_NAME);
	}

	if (infos->mapFd != -1)
	{
		close(infos->mapFd);
		if (infos->init == true)
			shm_unlink(GAME_NAME);
	}

	if (infos->msgId != -1)
	{
		if (infos->init == true)
			msgctl(infos->msgId, IPC_RMID, NULL);
	}

	if (infos->map != NULL)
	{
		for (int i = 0; infos->map[i] != NULL; i++)
			free(infos->map[i]);
		free(infos->map);
	}

	if (infos->realMap != NULL)
		munmap(infos->realMap, sizeof(char) * 96);
	infos->realMap = NULL;
}

void	endSignal(const int signal)
{
	writeStr(ERASE_LINE, 2);
	writeStr(END_MSG, 2);

	// if (data->init == true)
		// data->realMap[data->coord] = '#';

	endFree(data);

	exit(1);
}

int	main(const int argc, const char** arg)
{	
	if (argc == 2 && isHelp(arg[1]) == true)
		{ printHelp(); return (0); }
	else
	{
		if (argc != 2 || getStrLen(arg[1]) != 1 \
			|| isDigit(arg[1][0]) == false || arg[1][0] == '0')
		{
			writeStr("Error! Invalid arguments.\n", 2);
			writeStr("See -h or --help for more informations.\n", 2);

			return (1);
		}
	}

	tInfos	infos;

	// shm_unlink(GAME_NAME);
	// sem_unlink(ACC_NAME);
	// exit(0);

	data = &infos;
	signal(SIGINT, endSignal);
	signal(SIGSEGV, endSignal);

	setToNull(&infos);

	initializeRoutine(&infos, arg[1]);
	startRoutine(&infos);

	endFree(&infos);

	return (0);
}
