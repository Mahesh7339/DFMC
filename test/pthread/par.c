#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include "errorMsg.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

#define MAXPENDING 5
#define RECVBUFF 32
#define BUFFSIZE 32

void DieWithError(char *errorMsg);
void HandleTCPClient(int clientSock);

int *ethernet(int _argc, char *_argv[])
{
	int serverSock;
	int clientSock;
	struct sockaddr_in echoServAddr;
	struct sockaddr_in echoClientAddr;
	unsigned short echoServPort;
	unsigned int clientLen; /*Lenght of client data structure */

/*	if (argc2 != 2) {
		fprintf(stderr, "Usage: %s <Server Port> \n", argv2[0]);
		exit(1);
	}
*/
	echoServPort = atoi(_argv[2]);

	/* Creating a socket */
	if((serverSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
		DieWithError("\n \033[0;31m [SERVER] \033[0m Creation of socket failed");
	printf(" \n \033[0;32m [SERVER] \033[0m Socket created");
	/*Constucting socket address structure */
	memset(&echoServAddr, 0, sizeof(echoServAddr));
	echoServAddr.sin_family		=AF_INET;
	echoServAddr.sin_addr.s_addr	=htonl(INADDR_ANY);
	echoServAddr.sin_port		=htons(echoServPort);

	/*Binding with address*/

	if (bind(serverSock, (struct sockaddr *)&echoServAddr, sizeof(echoServAddr)) < 0)
		DieWithError("\n \033[0;31m [SERVER] \033[0m Binding failed");
	printf("\n \033[0;32m [SERVER] \033[0m Binding Success");
	/*Marking th esocket so that it listens for incoming connections */

	if (listen(serverSock, MAXPENDING) < 0)
		DieWithError("\n \033[0;31m [SERVER] \033[0m Listen failed");

	printf("\n \033[0;32m [SERVER] \033[0m Listen Success");
	/*run forever */

	for(;;) {
		clientLen = sizeof(echoClientAddr);

		/*wait for client ot accept*/

		if((clientSock = accept(serverSock, (struct sockaddr *)&echoClientAddr, &clientLen)) < 0)
			DieWithError("\n \033[0;31m [SERVER] \033[0m Accept Failed");
		printf("\n \033[0;32m [SERVER] \033[0m Accept Success");
		printf("\n \033[0;32m [SERVER] \033[0m Handling client: %s \n", inet_ntoa(echoClientAddr.sin_addr));
		HandleTCPClient(clientSock);

/*free the struct used for arguments*/
		free (args);
  		pthread_exit (NULL);

	}


}

void HandleTCPClient(int clientSock)
{
	char echoBuffer[RECVBUFF];
	int recvMsgSize; /*Size of received message */

	/*Receive message form client */
	if((recvMsgSize = recv(clientSock, echoBuffer, RECVBUFF, 0)) < 0)
		DieWithError("\n \033[0;31m [SERVER] \033[0m Receive Failed or closed prematurely(Handle tcp)");
	printf("\n \033[0;32m [SERVER] \033[0m Receive Success from Client (%d bytes)", recvMsgSize);
	/* Send received string and recieve until end of transmission */
	printf("\n [TEST] String Received:%s ", echoBuffer);
	while (recvMsgSize > 0) {
		/*Echo back to client*/
		if(send(clientSock, echoBuffer, recvMsgSize, 0) != recvMsgSize)
			DieWithError("\n \033[0;31m [SERVER] \033[0m Sending message failed");
		printf("\n \033[0;32m [SERVER] \033[0m Receive Sucess (%d bytes)", recvMsgSize);
		/* See if there is more data to receive */
		if((recvMsgSize = recv(clientSock, echoBuffer, RECVBUFF, 0)) < 0)
			DieWithError("\n \033[0;31m [SERVER] \033[0m Recieve Failed");
		printf("\n [TEST] Received String:%s ", echoBuffer);

	}
	close(clientSock);

}

void DieWithError(char *errorMsg1)
{

	perror(errorMsg1);
	exit(1);
}





int *uart(int _argc, char *_argv[])
{


	int fd;
	struct termios SerialSettings;
	_argc = argc1;
	_argv[]= argv1[];
/*      if (_argc!=3) {
		
		fprintf(stderr, "Usage:%s </dev/ttyXXX> \n", argv1[0]);
		exit(0);
	}
*/
	if((fd=open(_argv[1], O_RDWR | O_NOCTTY)) < 0)
		DieWithError("\n Cannot open port!");
	printf("\n %s opened succesfully!", _argv[1]);

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
	printf("\n Enter message to be transmitted:");
	while ((fgets(write_buffer, BUFFSIZE, stdin)) != NULL) {
	if((bytes = write(fd,write_buffer,sizeof(write_buffer))) < 0 ) 
		DieWithError("\n Sending Failed");
		}

	close(fd);

}

NTHREADS = 2;

int main(int argc, char *argv[])
{

       struct thread_args {
       int argc1;
       const char *argv1;
     };
  pthread_t threads[NTHREADS];
  struct thread_args *args = malloc (sizeof (struct thread_args));
  args->argc1   = argc;
  args->argv1[] = argv[];

  int rc;

  /* spawn the threads */
	if(argc!= 3)
	{
	fprintf(stderr,"Usage:%s </dev/ttyXXX>  <Server Port> \n",argv[0]);
	exit(0);	
	}

    
      printf("spawning thread 0\n",);
      rc = pthread_create(&threads[0], NULL, uart,args);
      printf("spawning thread 1\n",);
      rc = pthread_create(&threads[1], NULL, ethernet,args);


  /* wait for threads to finish */
    rc = pthread_join(threads[0], NULL);
    rc = pthread_join(threads[1], NULL);


  return 1;
}

