#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define MAXPENDING 5
#define RECVBUFF 32
void DieWithError(char *errorMsg);
void HandleTCPClient(int clientSock);

int main(int argc, char *argv[])
{
	int serverSock;
	int clientSock;
	struct sockaddr_in echoServAddr;
	struct sockaddr_in echoClientAddr;
	unsigned short echoServPort;
	unsigned int clientLen; /*Lenght of client data structure */

	if (argc != 2) {
		fprintf(stderr, "Usage: %s <Server Port> \n", argv[0]);
		exit(1);
	}

	echoServPort = atoi(argv[1]);

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
