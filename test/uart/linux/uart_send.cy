#include <stdlib.h>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include "errorMsg.h"

int main(int argc, char *argv[])
{


	int fd;
	if (argc!=2) {
		fprintf(stderr, "Usage:%s </dev/ttyXXX> \n", argv[0]);
		exit(0);
	}

	if((fd=open(argv[1], O_RDWR | O_NOCTTY)) < 0)
		DieWithError("\n Cannot open port!");
	printf("\n %s opened succesfully!");

	close(fd);

}
