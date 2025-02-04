#include "../../include/header.h"

int	getStrLen(const char* str)
{
	int	len = 0;
	for (int i = 0; str[i] != '\0'; i++)
		len++;

	return (len);
}

bool	isDigit(const char nb)
{
	if (nb < 48 || nb > 57)
		return (false);
	
	return (true);
}
