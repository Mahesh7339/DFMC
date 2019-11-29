#include <stdlib.h>
#include <stdio.h>



void DieWithError(char *errorMsg) 
{

	perror(errorMsg);
	exit(1);
}
