/*
    Server side code for TCP connection
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
void main()
{
    char *ip = "127.0.0.1";
    int port = 434525;            // should be same as client port
    int server_sock, client_sock; // server and client socket file descriptors
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;
    char buffer[1024];
    int bind_val;

    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock < 0)
    {
        perror("[-] Socket error ");
        exit(1);
    }
    printf("[+] TCP server socket created .\n");

    memset(&server_addr, '\0', sizeof(server_addr)); // clear the server_addr
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = port;
    server_addr.sin_addr.s_addr = inet_addr(ip);

    bind_val = bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (bind_val < 0)
    {
        perror("[-] Bind error ");
        exit(1);
    }
    printf("[+] Bind to the port number :%d\n", port);

    listen(server_sock, 10);
    printf(" Listening ...\n");

    while (1)
    {
        addr_size = sizeof(client_addr);
        client_sock = accept(server_sock, (struct sockaddr *)&client_addr, &addr_size);
        printf("[+] Clientconnected .\n");
        printf(" Client IP : %s\n", inet_ntoa(client_addr.sin_addr));
        bzero(buffer, 1024); // clear the buffer
        recv(client_sock, buffer, sizeof(buffer), 0);
        printf(" Client : %s\n", buffer);
        bzero(buffer, 1024);
        strcpy(buffer, "HELLO , THIS IS SERVER ");
        printf(" Server : %s\n", buffer);
        send(client_sock, buffer, strlen(buffer), 0);
        close(client_sock);
        printf("[+] Client disconnected.\n\n");
    }
    printf("Closing server \n");
    close(server_sock);
}
