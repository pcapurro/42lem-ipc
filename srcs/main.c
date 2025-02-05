#include "../include/header.h"

void	setToNull(tInfos* infos)
{
	infos->mapFd = -1;
	infos->msgFd = -1;
	infos->team = 0;

	infos->init = false;

	infos->map = NULL;
	infos->messages = NULL;
}

void	endFree(tInfos* infos)
{
	if (infos->mapFd != -1)
	{
		close(infos->mapFd);
		close(infos->msgFd);

		if (infos->init == true)
		{
			shm_unlink("/game");
			shm_unlink("/messages");

			for (int i = 0; i != 10; i++)
				msgctl(infos->messages[i], IPC_RMID, NULL);
		}
	}

	if (infos->map != NULL)
		munmap(infos->map, sizeof(char) * 96);
	if (infos->messages != NULL)
		munmap(infos->messages, sizeof(int) * 10);
	infos->map = NULL;
	infos->messages = NULL;
}

int	main(const int argc, const char** arg)
{	
	if (argc == 2 && isHelp(arg[1]) == true)
		{ printHelp(); return (0); }
	else
	{
		if (argc != 2 || getStrLen(arg[1]) != 1 \
			|| isDigit(arg[1][0]) == false)
		{
			writeStr("Error! Invalid arguments.\n", 2);
			writeStr("See -h or --help for more informations.\n", 2);

			return (1);
		}
	}

	tInfos	infos;

	// shm_unlink("/game"), shm_unlink("/messages"), exit(0);

	setToNull(&infos);

	initializeRoutine(&infos, arg[1]);
	startRoutine(&infos);

	endFree(&infos);

	return (0);
}
