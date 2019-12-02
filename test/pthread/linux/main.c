#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <pthread.h>
#include "functions.h"

#define NTHREADS 2

/*Function prototypes */
//void DieWithError(char *errorMsg);
//void HandleTCPClient(int clientSock);
//void *ethernet(void *arg);
//void *uart(void *arg);


int main()
{
  
  pthread_t threads[NTHREADS];
  int rc;

 /* Spawning the threads */   
      printf("spawning thread 0\n");
      rc = pthread_create(&threads[0], NULL, &uart,NULL);
      printf("spawning thread 1\n");
      rc = pthread_create(&threads[1], NULL, &ethernet,NULL);


  /* wait for threads to finish */
    rc = pthread_join(threads[0], NULL);
    rc = pthread_join(threads[1], NULL);


  return 0;
}




