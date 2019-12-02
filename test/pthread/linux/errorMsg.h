#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

void DieWithError(char *errorMsg1)
{

	perror(errorMsg1);
	exit(1);
}



