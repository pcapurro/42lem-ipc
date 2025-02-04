#include "../include/header.h"

int	main(const int argc, const char** arg)
{
	if (argc == 2 && isHelp(arg[1]) == true)
		{ printHelp(); return (0); }
	else
	{
		if (argc != 3 || getStrLen(arg[1]) != 1 || getStrLen(arg[2]) != 1 \
			|| isDigit(arg[1][0]) == false || isDigit(arg[1][0]) == false)
		{
			writeStr("Error! Invalid arguments.\n", 2);
			writeStr("See -h or --help for more informations.\n", 2);

			return (1);
		}
	}

	return (0);
}
