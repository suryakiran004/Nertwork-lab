#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
int main(){
int readByte;
int clientSocket;
struct sockaddr_in serverAddress;
char messsageBuffer[1024];
clientSocket = socket(AF_INET , SOCK_STREAM , 0);
//config
serverAddress.sin_family = AF_INET;
serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
serverAddress.sin_port = htons(8080);
connect(clientSocket ,
(struct sockaddr*)&serverAddress ,
sizeof(serverAddress));
printf("server connected successfully...");
while(1){
printf("Client : ");
fgets(messsageBuffer,sizeof(messsageBuffer),stdin);
send(clientSocket,messsageBuffer,strlen(messsageBuffer),0);
if(strncmp(messsageBuffer , "exit" , 4)==0){
break;
}
readByte = read(clientSocket,messsageBuffer,sizeof(messsageBuffer));
messsageBuffer[readByte]='\0';
printf("Server : %s",messsageBuffer);
}
close(clientSocket);
return 0;
}
