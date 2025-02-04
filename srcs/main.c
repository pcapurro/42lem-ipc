#include "../include/header.h"

void	setToNull(tInfos* infos)
{
	infos->fd = -1;
	infos->team = 0;

	infos->init = false;

	infos->map = NULL;
}

void	endFree(tInfos* infos)
{
	if (infos->fd != -1)
	{
		close(infos->fd);
		if (infos->init == true)
			shm_unlink("/game");
	}

	if (infos->map != NULL)
		munmap(infos->map, sizeof(char) * 96);
	infos->map = NULL;
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

	setToNull(&infos);

	initializeRoutine(&infos, arg[1]);
	startRoutine(&infos);

	endFree(&infos);

	return (0);
}
