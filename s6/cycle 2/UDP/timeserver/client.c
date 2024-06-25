#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define UDP_PORT 32324
#define MAX_BUFFER_SIZE 1024

int main() {
    int sock_fd, n;
    char buffer[MAX_BUFFER_SIZE];
    struct sockaddr_in serv_addr;

    if ((sock_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(UDP_PORT);

    if (inet_aton("127.0.0.1", &serv_addr.sin_addr) == 0) {
        perror("Invalid server address");
        exit(EXIT_FAILURE);
    }

    strcpy(buffer, "time");

    if (sendto(sock_fd, buffer, strlen(buffer), 0, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Error sending data");
        exit(EXIT_FAILURE);
    } else
        printf("time request to the server\n");

    n = recvfrom(sock_fd, buffer, MAX_BUFFER_SIZE, 0, NULL, NULL);
    if (n < 0) {
        perror("Error receiving data");
        exit(EXIT_FAILURE);
    } else
        printf("Received system time from the server\n");

    buffer[n] = '\0';
    printf("System time: %s\n", buffer);

    return 0;
}
