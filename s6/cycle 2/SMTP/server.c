#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define domain "server.smtp.com"

void main()
{
    int server_sock, client_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;
    char buffer[2000];

    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock < 0)
    {
        perror("Socket error\n");
        exit(1);
    }

    memset(buffer, '\0', 1024);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(5000);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.100");

    if (bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("Bind error\n");
        exit(1);
    }

    listen(server_sock, 20);

    addr_size = sizeof(client_addr);
    client_sock = accept(server_sock, (struct sockaddr *)&client_addr, &addr_size);

    printf("Client connected\n");

    bzero(buffer, 2000);
    recv(client_sock, buffer, 2000, 0);
    printf("Mail received:\n");
    printf("***********************************************\n");
    printf("%s\n", buffer);
    printf("***********************************************\n");

    close(server_sock);
}