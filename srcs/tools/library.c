#include "../../include/header.h"

int	getStrLen(const char* str)
{
	int	len = 0;
	for (int i = 0; str[i] != '\0'; i++)
		len++;

	return (len);
}
