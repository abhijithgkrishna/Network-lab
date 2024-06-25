#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

void main()
{
    int server_sock;
    struct sockaddr_in server_addr;
    socklen_t addr_size;

    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock < 0)
    {
        perror("Socket error\n");
        exit(1);
    }

    memset(&server_addr, '\0', sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(5000);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.100");

    connect(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr));

    char buffer[1024];
    int choice;
    char filename[100];
    FILE *fptr;
    while (1)
    {
        printf("\n1. Upload a file(PUT)\n2. Download a file(GET)\n3. Exit(BYE)\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            bzero(buffer, 1024);
            strcpy(buffer, "PUT");
            printf("Enter filename: ");
            scanf("%s", filename);
            fptr = fopen(filename, "r");
            if (!fptr)
                perror("File doesn't exist!\n");
            else
            {
                send(server_sock, buffer, 1024, 0);
                bzero(buffer, 1024);
                strcpy(buffer, filename);
                send(server_sock, buffer, 1024, 0);

                bzero(buffer, 1024);
                while (!feof(fptr))
                {
                    bzero(buffer, 1024);
                    fscanf(fptr, "%[^\n] ", buffer);
                    send(server_sock, buffer, 1024, 0);
                }
                bzero(buffer, 1024);
                strcpy(buffer, "END$");
                send(server_sock, buffer, 1024, 0);
                fclose(fptr);
                printf("File %s sent\n", filename);
            }
            break;

        case 2:
            bzero(buffer, 1024);
            strcpy(buffer, "GET");
            send(server_sock, buffer, 1024, 0);
            bzero(buffer, 1024);
            recv(server_sock, buffer, 1024, 0);
            printf("Process id: %s\n", buffer);

            printf("Enter filename: ");
            scanf("%s", filename);
            bzero(buffer, 1024);
            strcpy(buffer, filename);
            send(server_sock, buffer, 1024, 0);

            bzero(buffer, 1024);
            recv(server_sock, buffer, 1024, 0);

            if (strcmp(buffer, "404") == 0)
                printf("File does not exist in remote server\n");
            else if (strcmp(buffer, "200") == 0)
            {
                fptr = fopen(filename, "w");
                while (1)
                {
                    recv(server_sock, buffer, 1024, 0);
                    if (strcmp(buffer, "END$") == 0)
                        break;
                    fprintf(fptr, "%s", buffer);
                    bzero(buffer, 1024);
                }
                fclose(fptr);
                printf("File %s received\n", filename);
            }
            break;
        case 3:
            bzero(buffer, 1024);
            strcpy(buffer, "BYE");
            send(server_sock, buffer, 1024, 0);
            close(server_sock);
            exit(0);
        }
    }
}

