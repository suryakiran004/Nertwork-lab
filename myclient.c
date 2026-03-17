#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/type.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
int main()
{
  struct sockaddr_in client, server;
  int s, n;
  char b1[100], b2[100];
  s = socket(AF_INET, SOCK_DGRAM, 0);

  server.sin_family = AF_INET;
  server.sin_port = 2000;
  server.sin_addr.s_addr = inet_addr("127.0.0.1");

  bind(s, (struct sockaddr *)&server, size of(server));

  while(1)
    {
      recvfrom(s, b1, sizeof(b1), 0, (struct sockaddr *)&client, &n);
      if(!(strcmp(b1, "exit")))
        break;
      printf("\nClient: %s",b1);
      printf("\nServer: ");
      fgets(b2, sizeof(b2), stdin);
      sendto(s, b2, sizeof(b2), 0, (struct sock_addr *)&client, n);
    }
}
