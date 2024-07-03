/*
    UDP client using C
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <arpa/inet.h>

void main()
{
    char *server_ip = "127.0.0.1";
    int server_port = 5566;
    int sockfd;
    struct sockaddr_in server_addr;
    char buffer[1024];
    socklen_t addr_size;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0)
    {
        perror("[ -] Socket error ");
        exit(1);
    }

    // Creating the server address structure in order to connect to the server.
    memset(&server_addr, '\0', sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server_port);
    server_addr.sin_addr.s_addr = inet_addr(server_ip);

    bzero(buffer, 1024);
    printf(" Enter the data : ");
    scanf(" %[^\n]", buffer);
    printf("( Client ) Data to server :%s\n", buffer);
    sendto(sockfd, buffer, 1024, 0, (struct sockaddr *)&server_addr, sizeof(server_addr));

    bzero(buffer, 1024);

    recvfrom(sockfd, buffer, 1024, 0, (struct sockaddr *)&server_addr, &addr_size);
    printf("( Client ) Data from server :%s\n", buffer);
}
