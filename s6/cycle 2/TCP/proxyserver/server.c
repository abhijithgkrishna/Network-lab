# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <arpa/inet.h>
# include <string.h>

void main ()
{
    char *ip = "127.0.0.1";
    int port = 34243;

    int server_sock, client_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;
    char buffer[1024];

    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock < 0)
    {
        perror("[-] Socket error\n");
        exit(1);
    }

    memset(&server_addr, '\0', sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(ip);

    int n = bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (n < 0)
    {
        printf("[-] Bind error\n");
        exit(1);
    }

    listen(server_sock, 10);

    while (1)
    {
        addr_size = sizeof(client_addr);

        client_sock = accept(server_sock, (struct sockaddr *)&client_addr, &addr_size);
        printf("Server: Proxy server connected\n");

        bzero(buffer, 1024);
        recv(client_sock, buffer, 1024, 0);
        printf("Client: %s\n", buffer);

        bzero(buffer, 1024);
        strcpy(buffer, "Hello from the server!");
        printf("Server: %s\n", buffer);
        send(client_sock, buffer, strlen(buffer), 0);
    }
}
