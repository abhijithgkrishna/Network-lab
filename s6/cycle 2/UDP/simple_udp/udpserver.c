/*
    UDP Server using C
    Unlike TCP, UDP is connectionless.
    In this program, we will create a UDP server that will receive data from the client
    and send a response back to the client.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <ctype.h>

void main()
{
    char *ip = "127.0.0.1";
    int port = 5566;
    int sockfd;
    struct sockaddr_in server_addr, client_addr;
    char buffer[1024];
    socklen_t addr_size;
    int bind_val;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0)
    {
        perror("[-] Socket error");
        exit(1);
    }

    memset(&server_addr, '\0', sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(ip);

    addr_size = sizeof(server_addr);

    bind_val = bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (bind_val < 0)
    {
        perror("[+] Bind error");
        exit(1);
    }

    bzero(buffer, 1024);
    recvfrom(sockfd, buffer, 1024, 0, (struct sockaddr *)&client_addr, &addr_size); // the address of client gets stored in client_addr
    printf("[+] Data from client: %s\n", buffer);

    strcpy(buffer, "Data successfully received.");
    printf("(Server) Data to client: %s\n", buffer);

    int b = sendto(sockfd, buffer, 1024, 0, (struct sockaddr *)&client_addr, sizeof(client_addr));
    printf("Number of bytes sent : %d \n", b);
}
