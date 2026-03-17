#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main()
{
  struct sockaddr_in client, server;
  int s, n;
  char b1[100], b2[100];

  s = socket(AF_INET, SOCK_DGRAM, 0);

  server.sin_family=AF_INET;
  server.sin_port=2000;
  server.sin_addr.s_addr=inet_addr("127.0.0.1");

  printf("\nClient ready..\n");
  n=sizeof(server);

  while(1)
    {
      Printf("Client: ");
      fgets(b1, sizeof(b1), stdin);
      b2[strcspn(b2, "\n")]='\0';
      sendto(s, b1, sizeof(b1), 0, (struct sockaddr *)&server, n);
      if(!(strcmp(b1, "exit")))
      {
        printf("\nClient exit\n");
        break;
      }
      recvfrom(s, b2, sizeof(b2), 0, NULL, NULL);
      printf("\nServer: %s\n",b1);
    }
  return 0;
}
