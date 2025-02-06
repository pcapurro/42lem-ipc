#include "../include/header.h"

void	setToNull(tInfos* infos)
{
	infos->mapFd = -1;
	infos->team = 0;

	infos->init = false;
	infos->playersNb = 1;
	infos->teamsNb = 1;

	infos->msgId = -1;
	infos->realMap = NULL;
	infos->map = NULL;

	infos->coord = -1;
	infos->alive = false;
}

void	endFree(tInfos* infos)
{
	if (infos->mapFd != -1)
	{
		close(infos->mapFd);
		if (infos->init == true)
			shm_unlink(GAME_NAME);
	}

	if (infos->msgId != -1)
	{
		close(infos->msgId);
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

	// shm_unlink(GAME_NAME), exit(0);

	tInfos	infos;

	setToNull(&infos);

	initializeRoutine(&infos, arg[1]);
	startRoutine(&infos);

	endFree(&infos);

	return (0);
}
