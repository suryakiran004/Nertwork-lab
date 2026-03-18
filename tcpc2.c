#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

#define port 8080 

int main() {
    int readbytes;
    int c; 
    struct sockaddr_in server;
    char buff[1024];

    c = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(port);

    if (connect(c, (struct sockaddr*)&server, sizeof(server)) < 0) {
        return 1;
    }
    
    printf("Server connected successfully...\n");

    while (1) {
        printf("Client: ");
        fgets(buff, sizeof(buff), stdin);
        send(c, buff, strlen(buff), 0);

        if (strncmp(buff, "exit", 4) == 0) {
            break;
        }

        readbytes = read(c, buff, sizeof(buff));
        if (readbytes > 0) {
            buff[readbytes] = '\0';
            printf("Server: %s", buff);
        }

        if (strncmp(buff, "exit", 4) == 0) {
            break;
        }
    }

    close(c);
    return 0;
}
