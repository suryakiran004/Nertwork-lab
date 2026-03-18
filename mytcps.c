#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#define port 8080;
int main()
{
  int s, c;
  struct sockaddr_in client, server;
  socklen_t n=sizeof(client);
  int readbytes;
  char buff[1024];

  s=socket(AF_INET, SOCK_STREAM, 0);

  server.sin_family=AF_INET;
  server.sin_addr.s_addr=INADDR_ANY;
  server.sin_port=htons(port);

  bind(s, (struct sockaddr *)&server, sizeof(server));

  

  listen(s, 5);

  printf("waitin for connection");

  c = accept(s, (struct sockaddr *)&client, &n);

  printf("connected");

  while(1)
    {
      readbytes=read(c, buff, sizeof(buff));
      buff[readbytes]='\0';
      printf("\nClient: %s\n",buff);

      if(strncmp(buff, "exit", 4)==0)
      {
        break;
      }

      printf("\nServer: ");
      fgets(buff, sizeof(buff),stdin);
      send(c, buff, strlen(buff), 0);

      if (strncmp(messageBuffer, "exit", 4) == 0){
        break;
      }
    }
  close s;
  close c;
  return 0;
}
