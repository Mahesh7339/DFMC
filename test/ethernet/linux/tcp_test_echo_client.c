#include <stdio.h> /*Printf and fprintf*/
#include <sys/socket.h> /*Socket, open, recv, send */
#include <arpa/inet.h>  /*Sockaddr_in, inet_addr */
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define RECVBUFF 32

void DieWithError(char *errMsg);

int main(int argc, char *argv[]) 
{
	int sock;			 /*Socket descriptor*/
	struct sockaddr_in echoServAddr; /*Echo server address*/
	unsigned int echoServPort; 	 /*Echo server port*/
	char* servIP;			/*Server iP address*/
	char *echoString;		/*String to send to echo server*/
	unsigned int echoStringLen;
	char echoBuffer[RECVBUFF];	/*Buffer for echo string*/
	int BytesRecv, totalBytesRecv;


	if ((argc < 3) || (argc > 4)) {
		fprintf(stderr, "Usage: %s <Server IP> <Echo Word> [<Echo Port>] \n", argv[0]);
		exit(1);
	}

	servIP = argv[1];
	echoString = argv[2];

	if (argc == 4) 
		echoServPort = atoi(argv[3]);
	else
		echoServPort = 7;

	/* Creation of scoket */

	if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
		DieWithError("Creation of Socket Failed");


	/* Construct server adress*/

	memset(&echoServAddr, 0, sizeof(echoServAddr));
	echoServAddr.sin_family		= AF_INET;
	echoServAddr.sin_addr.s_addr	=inet_addr(servIP);
	echoServAddr.sin_port		=htons(echoServPort);

	/*Establish connection */
	if(connect(sock, (struct sockaddr *)&echoServAddr, sizeof(echoServAddr)) < 0)
		DieWithError("Connection failed");

	echoStringLen = strlen(echoString);

	/*Sending the string */

	if(send(sock, echoString, echoStringLen, 0) != echoStringLen)
		DieWithError("Send sent different bytes than expected");


	/* Receiveing the same string */
	totalBytesRecv = 0;
	printf("Received: ");
	while(totalBytesRecv < echoStringLen) {
		/*receive upto buffer size -q , so that there is space for the null
			character */
		if((BytesRecv = recv(sock, echoBuffer, RECVBUFF -1, 0)) <=0)
			DieWithError("Recv closed prematurely");
		totalBytesRecv += BytesRecv;
		echoBuffer[BytesRecv] = '\0';
		printf(echoBuffer);
	}
	printf("\n");
	close(sock);
	exit(0);
}






