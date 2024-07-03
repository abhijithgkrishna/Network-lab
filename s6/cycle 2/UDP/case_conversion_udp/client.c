#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

int main()
{
    int sock;
    char buffer[128];
    struct sockaddr_in server_addr;
    socklen_t serverlen;
    int server_port = 334332;
    char *server_ip = "127.0.2.1";

    sock = socket(PF_INET, SOCK_DGRAM, 0);
    if (sock == -1)
    {
        printf("Error : Socket creation failed");
        exit(1);
    }

    memset(&server_addr, '\0', sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server_port);
    server_addr.sin_addr.s_addr = inet_addr(server_ip);

    bzero(buffer, 128);
    printf("Enter data to send to server : ");
    scanf("%s", buffer);
    printf("Sending data to server ... \n");

    serverlen = sizeof(server_addr);

    sendto(sock, buffer, 128, 0, (struct sockaddr *)&server_addr, serverlen);
    recvfrom(sock, buffer, 128, 0, (struct sockaddr *)&server_addr, &serverlen);
    printf("Server : %s ", buffer);
    printf("Enter option : ");
    scanf("%s", buffer);
    printf("Sending data to server ... \n");
    sendto(sock, buffer, 128, 0, (struct sockaddr *)&server_addr, sizeof(server_addr));
    recvfrom(sock, buffer, 128, 0, (struct sockaddr *)&server_addr, &serverlen);
    printf("Server : %s \n", buffer);
}