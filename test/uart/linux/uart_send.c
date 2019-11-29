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

	if((fd=open(argv[1], O_RDWR | O_NOCTTY)) < 0)
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



	char write_buffer[BUFFSIZE];
	int bytes  =  0 ;
	printf("\n Enter message to be transmitted:(Type quit to quit)");
	fgets(write_buffer, BUFFSIZE, stdin);
	while (strcmp(write_buffer, "quit\n") != 0 ) {
	if((bytes = write(fd,write_buffer,strlen(write_buffer))) < 0 ) 
		DieWithError("\n Sending Failed");
	printf("\n Sending \033[0;32m %d \033[0m bytes. \n", bytes);
	//printf("\n Enter the next message to be transmitted(type quit to exit): ");
	memset(write_buffer, 0,  BUFFSIZE);
	fgets(write_buffer, BUFFSIZE, stdin);	
	}
	printf("\n \033[1;31m Exiting.. \033[0m \n");
	close(fd);

}
