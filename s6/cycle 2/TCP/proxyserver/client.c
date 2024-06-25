# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <arpa/inet.h>
# include <string.h>
# include <unistd.h>

void main ()
{
    char *ip = "127.0.0.22";
    int port = 34343;

    int sock;
    struct sockaddr_in server_addr;
    socklen_t addr_size;
    char buffer[1024];

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        perror("[ -] Socket error ");
        exit(1);
    }

    memset(&server_addr, '\0', sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(ip);

    connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr));
    printf("Connected to proxy server \n");

    bzero(buffer, 1024);
    strcpy(buffer, "Hello from client!");
    printf("Client: %s\n", buffer);
    send(sock, buffer, 1024, 0);

    bzero(buffer, 1024);
    recv(sock, buffer, sizeof(buffer), 0);
    printf("Proxy server: %s\n", buffer);

    close(sock);
}
