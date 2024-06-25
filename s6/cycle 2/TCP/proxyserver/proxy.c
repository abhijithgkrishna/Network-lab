# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <arpa/inet.h>
# include <string.h>
# include <unistd.h>

void main ()
{
    char *server_ip = "127.0.0.1";
    int server_port = 34243;

    char *proxy_ip = "127.0.0.22";
    int proxy_port = 34343;

    int server_sock, client_sock, proxy_sock;
    struct sockaddr_in server_addr, client_addr, proxy_addr;
    socklen_t server_addr_size, client_addr_size;
    char buffer[1024];

    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    proxy_sock = socket(AF_INET, SOCK_STREAM, 0);

    if (server_sock < 0 || proxy_sock < 0)
    {
        perror("[-] Socket error ");
        exit(1);
    }

    memset(&server_addr, '\0', sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server_port);
    server_addr.sin_addr.s_addr = inet_addr(server_ip);

    memset(&proxy_addr, '\0', sizeof(proxy_addr));
    proxy_addr.sin_family = AF_INET;
    proxy_addr.sin_port = htons(proxy_port);
    proxy_addr.sin_addr.s_addr = inet_addr(proxy_ip);

    int n = bind(proxy_sock, (struct sockaddr *)&proxy_addr, sizeof(proxy_addr));
    if (n < 0)
    {
        perror("[ -] Bind error \n");
        exit(1);
    }

    connect(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr));
    printf("Proxy server: Connected to server \n");

    listen(proxy_sock, 10);

    client_addr_size = sizeof(client_addr);
    client_sock = accept(proxy_sock, (struct sockaddr *)&client_addr, &client_addr_size);
    printf("Proxy server: Client connected \n");

    bzero(buffer, 1024);
    recv(client_sock, buffer, 1024, 0);
    printf("Client: %s\nProxy server: Sending message to server \n", buffer);

    send(server_sock, buffer, sizeof(buffer), 0);

    bzero(buffer, 1024);
    recv(server_sock, buffer, sizeof(buffer), 0);
    printf("Server: %s\nProxy server: Sending message to client \n", buffer);

    send(client_sock, buffer, sizeof(buffer), 0);
    close(server_sock);
}
