#include <stdio.h>
#include <sys/types.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>

void *server_communication(void *sockId)
{
    int sock = *((int *)sockId);
    while (1)
    {
        char data[128];
        bzero(data, sizeof(data));
        recv(sock, data, sizeof(data), 0);
        printf("%s\n", data);
    }
}

int main()
{
    int sock;
    int server_port = 23422;
    char *server_ip = "127.0.0.98";
    sock = socket(PF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_addr;

    pthread_t thread;

    char buffer[128];

    char username[32];

    if (sock < 0)
    {
        printf("Socket creation failed ");
        exit(1);
    }

    memset((struct sockaddr *)&server_addr, '\0', sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server_port);
    server_addr.sin_addr.s_addr = inet_addr(server_ip);

    printf("Enter Username : ");
    scanf("%s", username);

    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        printf("Bind failed \n");
        exit(1);
    }
    printf("Connected to server !\n");

    send(sock, username, sizeof(username), 0);

    pthread_create(&thread, NULL, server_communication, (void *)&sock);

    while (1)
    {
        scanf("%s", buffer);
        printf("%30s\n", buffer);
        send(sock, buffer, sizeof(buffer), 0);
    }
}