#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#define port 8080
int main(){
  int serverSocket, clientSocket;
  struct sockaddr_in serverAdderss;
  struct sockaddr_in clientAddress;
  socklen_t clientLength = sizeof(clientAddress);
  int readBytes;
  char messageBuffer[1024];
  serverSocket = socket(AF_INET,SOCK_STREAM,0);
  serverAdderss.sin_family=AF_INET;
  serverAdderss.sin_addr.s_addr=INADDR_ANY;
  serverAdderss.sin_port=htons(port);
  bind(serverSocket , (struct sockaddr*)&serverAdderss , sizeof(serverAdderss) );
  listen(serverSocket,5);
  printf("Waiting for connection ... \n");
  clientSocket = accept(serverSocket , (struct sockaddr*)&clientAddress , &clientLength);
  printf("client conected successfully ... ");
  while (1){
    readBytes = read(clientSocket , messageBuffer , sizeof(messageBuffer));
    messageBuffer[readBytes] = '\0';
    printf("client : %s ", messageBuffer);
    if (strncmp(messageBuffer , "exit" , 4 ) == 0) {
      break;
    }
    printf("server : ");
    fgets(messageBuffer , sizeof(messageBuffer) , stdin );
    send(clientSocket , messageBuffer , strlen(messageBuffer) , 0 );
    if (strncmp(messageBuffer , "exit" , 4) == 0){
      break;
    }
  }
  close(serverSocket);
  close(clientSocket);
  return 0;
}
