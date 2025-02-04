#ifndef HEADER_H
# define HEADER_H

# include <unistd.h>
# include <stdbool.h>

# define SYSTEM_FAILED "Error! System failed."
# define MEMORY_FAILED "Error! Memory failed."

int		getStrLen(const char* str);
void	writeStr(const char* str, const int fd);

void	systemFailed(void);
void	memoryFailed(void);

void	printHelp(void);
bool	isHelp(const char* str);

int		main(const int argc, const char** arg);

#endif