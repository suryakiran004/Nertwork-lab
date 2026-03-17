#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/time.h>

#define PORT 8090
#define BUFFER_SIZE 1024
#define TIMEOUT 3

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE] = {0};
    char packet[50];
    struct timeval tv;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        perror("Invalid address");
        exit(EXIT_FAILURE);
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    printf("Client: Connected to server.\n");

    tv.tv_sec = TIMEOUT;
    tv.tv_usec = 0;
    setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof(tv));

    while (1) {

        printf("Enter packet number (or type exit): ");
        fgets(packet, sizeof(packet), stdin);
        packet[strcspn(packet, "\n")] = 0;

        send(sock, packet, strlen(packet), 0);

        // 🔴 If user types exit → terminate
        if (strcmp(packet, "exit") == 0) {
            printf("Client: Exit sent. Closing connection.\n");
            break;
        }

        int valread = read(sock, buffer, BUFFER_SIZE);

        if (valread > 0 && strcmp(buffer, "ACK") == 0) {
            printf("Client: ACK received\n\n");
        } else {
            printf("Client: Timeout! Retransmitting...\n\n");
        }

        memset(buffer, 0, BUFFER_SIZE);
    }

    close(sock);
    return 0;
}
