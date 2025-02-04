#include "../../include/header.h"

void	startRoutine(tInfos* infos)
{
	printf("starting routine...\n");

	int k = 0;
	while (1)
	{
		for (int i = 0; infos->map[i] != '\0'; i++)
		{
			if (i % 16 == 0 && i != 0)
				printf("\n");
			printf("%c ", infos->map[i]);
		}
		printf("\n");
		printf("\n");

		sleep(1);
		k++;

		if (k == 7)
			return ;
	}
}
