#include "../../include/header.h"

void	writeStr(const char* str, const int fd)
{
	for (int i = 0; str[i] != '\0'; i++)
		write(fd, &str[i], sizeof(char));
}

void	removeElement(char** array, const int element)
{
	for (int i = 0; array[i] != NULL; i++)
	{
		for (int k = 0; array[i][k] != '\0'; k++)
		{
			if (array[i][k] == element)
				array[i][k] = '0';
		}
	}
}
