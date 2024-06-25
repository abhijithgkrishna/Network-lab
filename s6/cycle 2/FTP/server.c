#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

void main()
{
    int server_sock, client_sock;
    struct sockaddr_in server_addr, client_addr;
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

    int n = bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (n < 0)
    {
        perror("Bind error\n");
        exit(1);
    }

    listen(server_sock, 1024);

    addr_size = sizeof(client_addr);
    client_sock = accept(server_sock, (struct sockaddr *)&client_addr, &addr_size);

    char buffer[1024];
    char filename[100];
    FILE *fptr;
    while (1)
    {
        bzero(buffer, 1024);
        recv(client_sock, buffer, 1024, 0);

        if (strcmp(buffer, "PUT") == 0)
        {
            bzero(buffer, 1024);
            recv(client_sock, buffer, 1024, 0);
            strcpy(filename, buffer);
            bzero(buffer, 1024);
            fptr = fopen(filename, "w");
            while (1)
            {
                recv(client_sock, buffer, 1024, 0);
                printf("buffer = %s\n", buffer);
                if (strcmp(buffer, "END$") == 0)
                    break;
                fprintf(fptr, "%s", buffer);
                bzero(buffer, 1024);
            }
            printf("File %s received\n", filename);
            fclose(fptr);
        }

        else if (strcmp(buffer, "GET") == 0)
        {
            bzero(buffer, 1024);
            sprintf(buffer, "%d", getpid());
            send(client_sock, buffer, 1024, 0);
            bzero(buffer, 1024);
            recv(client_sock, buffer, 1024, 0);
            strcpy(filename, buffer);

            bzero(buffer, 1024);
            fptr = fopen(filename, "r");
            if (!fptr)
            {
                printf("File %s does not exist\n", filename);
                strcpy(buffer, "404");
                send(client_sock, buffer, 1024, 0);
            }

            else
            {
                strcpy(buffer, "200");
                send(client_sock, buffer, 1024, 0);

                while (!feof(fptr))
                {
                    bzero(buffer, 1024);
                    fscanf(fptr, "%[^\n] ", buffer);
                    send(client_sock, buffer, 1024, 0);
                }
                bzero(buffer, 1024);
                strcpy(buffer, "END$");
                send(client_sock, buffer, 1024, 0);
                fclose(fptr);
                printf("File %s sent\n", filename);
            }
        }

        else if (strcmp(buffer, "BYE") == 0)
        {
            close(server_sock);
            exit(0);
        }
    }
}

