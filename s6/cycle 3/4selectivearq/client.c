#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>

#define timeoutValue 5
#define packetCount 10
#define windowSize 3

typedef struct Packet
{
    int id;
    int sent;
} Packet;

Packet packets[packetCount];
pthread_t thread[packetCount], receiveThread;
int sockfd;
struct sockaddr_in addr;
int windowStart, windowEnd;
int nextToSend;

void *sendPacket(void *sendPacket)
{
    Packet *packet = (Packet *)sendPacket;
    char buffer[1024];

    while (packet->sent == 0)
    {
        printf("Client: Sending packet %d\n",packet->id);
        bzero(buffer, 1024);
        sprintf(buffer, "%d", packet->id);

        sendto(sockfd, buffer, 1024, 0, (struct sockaddr *)&addr, sizeof(addr));
        sleep(timeoutValue);
        if (packet->sent == 0)
            printf("Client: Timeout for packet %d\n", packet->id);
    }
}

void *receivePacket()
{
    socklen_t addr_size = sizeof(addr);
    char buffer[1024];

    while (1)
    {
        bzero(buffer, 1024);
        recvfrom(sockfd, buffer, 1024, 0, (struct sockaddr *)&addr, &addr_size);

        char msg[20];
        int packetID;

        sscanf(buffer, "%s%d", msg, &packetID);
        if (strcmp(msg, "NACK") == 0)
        {
            printf("Client: Received negative acknowledgment for packet %d\nSending again\n", packetID);
            pthread_cancel(thread[packetID - 1]);
            pthread_create(&thread[packetID - 1], NULL, sendPacket, (void *)&packets[packetID - 1]);
        }
        else if (strcmp(msg, "ACK") == 0)
        {
            printf("Client: Received acknowledgement for packet %d\n", packetID);
            packets[packetID - 1].sent = 1;
            if (windowStart == packetID - 1)
            {
                while (packets[windowStart].sent == 1)
                {
                    windowStart++;
                    if (windowEnd < packetCount)
                        windowEnd++;
                }
            }
        }
        else
            printf("Client: Invalid message\n");
    }
}

void main()
{
    for (int i = 0; i < packetCount; ++i)
    {
        packets[i].id = i + 1;
        packets[i].sent = 0;
    }

    char *ip = "127.0.0.100";
    int port = 55693;

    char buffer[1024];
    socklen_t addr_size;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0)
    {
        perror("[-]Socket error");
        exit(1);
    }

    memset(&addr, '\0', sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(ip);

    pthread_create(&receiveThread, NULL, receivePacket, NULL);

    windowStart = 0;
    windowEnd = windowStart + windowSize - 1;

    for (int i = windowStart; i <= windowEnd; ++i)
        pthread_create(&thread[i], NULL, sendPacket, (void *)&packets[i]);

    nextToSend = windowEnd + 1;
    while (windowStart != windowEnd)
    {
        if (nextToSend <= windowEnd && nextToSend<packetCount)
        {
            pthread_create(&thread[nextToSend], NULL, sendPacket, (void *)&packets[nextToSend]);
            nextToSend++;
        }
    }
    close(sockfd);
}
