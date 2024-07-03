/*
    Client side code of chat server using C
    We require two procesess to be running at the same time.
        1. Send messages to server
        2. Receive messages from server
    We create a thread for process 2 and make it print the incoming messages from server
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <pthread.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

void *serverCommunication(void *sockID)
{
    int clientSocket = *((int *)sockID);
    while (1)
    {
        char data[1024];
        bzero(data, 1024);
        int read = recv(clientSocket, data, 1024, 0);
        data[read] = '\0';
        printf("%s\n", data);
    }
}
void main()
{
    int clientSocket = socket(PF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(34343);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (connect(clientSocket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
        exit(0);
    printf(" Connection established ............\n");
    pthread_t thread;
    pthread_create(&thread, NULL, serverCommunication, (void *)&clientSocket);
    while (1)
    {
        char input[1024];
        scanf("%s", input);
        if (strcmp(input, "SEND") == 0)
        {
            send(clientSocket, input, 1024, 0);
            scanf("%s", input);
            send(clientSocket, input, 1024, 0);
            scanf("%[^\n]", input);
            send(clientSocket, input, 1024, 0);
        }
    }
}