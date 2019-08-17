#include "Functions.h"

void error_win_close()
{
	gm::Core::getWindow().close();
	system("pause");
	exit(EXIT_FAILURE);
}

bool inRange(unsigned low, unsigned high, unsigned x) 
{ 
    return  ((x-low) <= (high-low)); 
} 