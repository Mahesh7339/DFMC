#include <stdlib.h>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "errorMsg.h"

#define BUFFSIZE 32
int main(int argc, char *argv[])
{


	int fd;
	struct termios SerialSettings;
	if (argc!=2) {
		fprintf(stderr, "Usage:%s </dev/ttyXXX> \n", argv[0]);
		exit(0);
	}

	if((fd = open(argv[1], O_RDWR | O_NOCTTY)) < 0)
		DieWithError("\n Cannot open port!");
	printf("\n %s opened succesfully!", argv[1]);

	tcgetattr(fd, &SerialSettings);	


	cfsetispeed(&SerialSettings,B9600);
	cfsetospeed(&SerialSettings,B9600);
	
	SerialSettings.c_cflag &= ~PARENB; /*CLEAR Parity Bit PARENB*/
	SerialSettings.c_cflag |=  PARENB; /*SET   Parity Bit PARENB*/
	SerialSettings.c_cflag &= ~PARENB;   // No Parity	
	SerialSettings.c_cflag &= ~CSTOPB; //Stop bits = 1 
	SerialSettings.c_cflag &= ~CSIZE; /* Clears the Mask       */
	SerialSettings.c_cflag |=  CS8;   /* Set the data bits = 8 */
	SerialSettings.c_cflag &= ~CRTSCTS;
	SerialSettings.c_cflag |= CREAD | CLOCAL;
	SerialSettings.c_iflag &= ~(IXON | IXOFF | IXANY);
	SerialSettings.c_iflag &= ~(ICANON | ECHO | ECHOE | ISIG);

	tcsetattr(fd,TCSANOW,&SerialSettings);



	char read_buffer[BUFFSIZE];
	int bytes_read = 0;

	if((bytes_read = read(fd, &read_buffer, sizeof(read_buffer))) < 0)
		printf("Received 0 bytes");

	printf("\n String:%s", read_buffer);
	close(fd);

}
