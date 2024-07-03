#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

void convert_to_upper(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] >= 'a' && str[i] <= 'z')
            str[i] -= 32;
    }
}

void convert_to_lower(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] >= 'A' && str[i] <= 'Z')
            str[i] += 32;
    }
}

int main()
{
    int sockfd;
    char buffer[128];
    char client_msg[128];
    char *server_ip = "127.0.2.1";
    int server_port = 334332;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len;

    sockfd = socket(PF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1)
    {
        printf("Error creating socket \n");
        exit(1);
    }

    memset(&server_addr, '\0', sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server_port);
    server_addr.sin_addr.s_addr = inet_addr(server_ip);

    if ((bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr))) == -1)
    {
        printf("Error : Bind failed");
        exit(1);
    }
    bzero(buffer, 128);

    client_len = sizeof(client_addr);

    recvfrom(sockfd, buffer, 128, 0, (struct sockaddr *)&client_addr, &client_len);
    strcpy(client_msg, buffer);
    printf("Data from client : %s", client_msg);
    bzero(buffer, 128);
    strcpy(buffer, "Enter option : \n1. Convert to lowercase \n2. Covert to uppercase \n");
    sendto(sockfd, buffer, 128, 0, (struct sockaddr *)&client_addr, sizeof(client_addr));
    recvfrom(sockfd, buffer, 128, 0, (struct sockaddr *)&client_addr, &client_len);
    if (strcmp(buffer, "1") == 0)
    {
        convert_to_lower(client_msg);
        strcpy(buffer, client_msg);
    }
    else if (strcmp(buffer, "2") == 0)
    {
        convert_to_upper(client_msg);
        strcpy(buffer, client_msg);
    }
    else
    {
        strcpy(buffer, "Wrong option");
    }
    sendto(sockfd, buffer, 128, 0, (struct sockaddr *)&client_addr, sizeof(client_addr));
}