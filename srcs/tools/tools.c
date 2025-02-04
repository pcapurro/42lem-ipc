#include "../../include/header.h"

void	writeStr(const char* str, const int fd)
{
	for (int i = 0; str[i] != '\0'; i++)
		write(fd, &str[i], sizeof(char));
}
