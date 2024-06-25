#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define UDP_PORT 32324
#define MAX_BUFFER_SIZE 1024

int main() {
    int sock_fd, n;
    char buffer[MAX_BUFFER_SIZE];
    struct sockaddr_in serv_addr, cli_addr;
    socklen_t cli_len = sizeof(cli_addr);
    pid_t pid;

    if ((sock_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(UDP_PORT);

    if (bind(sock_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Error binding socket");
        exit(EXIT_FAILURE);
    }

    while (1) {
        n = recvfrom(sock_fd, buffer, MAX_BUFFER_SIZE, 0, (struct sockaddr *)&cli_addr, &cli_len);
        if (n < 0) {
            perror("Error receiving data");
            exit(EXIT_FAILURE);
        } else
            printf("Received client request\n");

        if ((pid = fork()) < 0) {
            perror("Error forking process");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            if (strcmp(buffer, "time") == 0) {
                time_t t = time(NULL);
                struct tm *tm = localtime(&t);
                char current_time[MAX_BUFFER_SIZE];
                strftime(current_time, MAX_BUFFER_SIZE, "%Y-%m-%d %H:%M:%S", tm);
                printf("%s\n", current_time);
                if (sendto(sock_fd, current_time, strlen(current_time), 0, (struct sockaddr *)&cli_addr, cli_len) < 0) {
                    perror("Error sending data");
                    exit(EXIT_FAILURE);
                } else
                    printf("Send current system time to the client\n");
            }
            exit(EXIT_SUCCESS);
        } else {
            close(cli_len);
        }
    }
    return 0;
}
