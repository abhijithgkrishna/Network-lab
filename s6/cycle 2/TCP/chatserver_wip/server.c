#include <stdio.h>
#include <sys/types.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>

int clientcount = 0;

struct client_detail
{
    int index;
    char username[32];
    int client_sock_id;
    struct sockaddr_in addr;
    int len;
};

struct client_detail client[128];
pthread_t thread[128];

void *client_communication(void *clientinfo)
{
    struct client_detail *clientdetail = (struct client_detail *)clientinfo;
    char user[32];
    strcpy(user, clientdetail->username);
    int clientsock = clientdetail->client_sock_id;
    int index = clientdetail->index;
    printf("%s Connected \n", clientdetail->username);
    while (1)
    {
        char data[128];
        char message[128];
        strcpy(message, user);
        strncat(message, " : ", 4);
        bzero(data, sizeof(data));
        recv(clientsock, data, sizeof(data), 0);
        strncat(message, data, sizeof(data));
        for (int i = 0; i < clientcount; i++)
        {
            send(client[i].client_sock_id, message, sizeof(message), 0);
        }
    }
}

int main()
{
    int sock;
    int server_port = 23422;
    char *server_ip = "127.0.0.98";
    struct sockaddr_in server_addr;

    sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        printf("Socket Creation failed");
        exit(1);
    }

    memset((struct sockaddr *)&server_addr, '\0', sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server_port);
    server_addr.sin_addr.s_addr = inet_addr(server_ip);

    if (bind(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        printf("Bind failed ");
        exit(1);
    }
    listen(sock, 10);
    while (1)
    {
        client[clientcount].client_sock_id = accept(sock, (struct sockaddr *)&client[clientcount].addr, &client[clientcount].len);
        client[clientcount].index = clientcount;
        recv(sock, client[clientcount].username, sizeof(client[clientcount].username), 0);
        pthread_create(&thread[clientcount], NULL, client_communication, (void *)&client[clientcount]);
        clientcount++;
    }
}