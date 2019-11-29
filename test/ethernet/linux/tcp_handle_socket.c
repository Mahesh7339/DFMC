#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define  RECVBUFF 32

void DieWithError(char *errorMsg);

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
