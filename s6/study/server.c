#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

void main()
{
    char *ip = "127.0.0.1";
    int port = 34532;
    int server_sock, client_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;
    char buffer[1024];
    int bindval;

    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock < 0)
    {
        printf("Socket creation failed \n");
        exit(1);
    }
    printf("Socket created successfully \n");
    memset(&server_addr, '\0', sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = port;
    server_addr.sin_addr.s_addr = inet_addr(ip);

    bindval = bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (bindval < 0)
    {
        printf("Bind Failed \n");
        exit(1);
    }
    printf("Bind successful \n");
    listen(server_sock, 10);
    printf("Listening \n");
    while (1)
    {
        addr_size = sizeof(client_addr);
        client_sock = accept(server_sock, (struct sockaddr *)&client_addr, &addr_size);
        printf("Client connected \n");
        bzero(buffer, 1024);
        recv(client_sock, buffer, sizeof(buffer), 0);
        printf("Data from client : %s \n", buffer);
        bzero(buffer, 1024);
        strcpy(buffer, "Hello this is server replying back");
        printf(" Server : %s\n", buffer);
        send(client_sock, buffer, sizeof(buffer), 0);
        close(client_sock);
        printf("Client disconnected\n");
    }
    printf("Closing server \n");
    close(server_sock);
}