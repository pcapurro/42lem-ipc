#include "../../include/header.h"

void	systemFailed(void)
{
	writeStr(SYSTEM_FAILED, 2);
}

void	memoryFailed(void)
{
	writeStr(MEMORY_FAILED, 2);
}
