#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

#define domain "server.smtp.com"

char *mailHeader(char *from, char *to, char *subject, char *content)
{
    char *header = (char *)malloc(2000);

    time_t t;
    time(&t);
    sprintf(header, "Date: %s", ctime(&t));
    sprintf(header + strlen(header), "From: %s\n", from);
    sprintf(header + strlen(header), "To: %s\n", to);
    sprintf(header + strlen(header), "-----------------------------------------\n\n");
    sprintf(header + strlen(header), "%s", content);

    return header;
}

void main()
{
    int server_sock;
    struct sockaddr_in server_addr;
    socklen_t addr_size;
    char buffer[2000];

    char subject[100], sender[100], recepient[100], content[1000];

    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock < 0)
    {
        perror("Socket error\n");
        exit(1);
    }

    memset(buffer, '\0', 2000);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(5000);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.100");

    connect(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr));
    printf("Connected to server\n");

    printf("<-- Send a mail -->\n");
    strcpy(sender, "client@");
    strcat(sender, domain);
    printf("Enter recepient mail: ");
    scanf("%[^\n]%*c", recepient);
    printf("Enter subject: ");
    scanf("%[^\n]%*c", subject);
    printf("Enter content: ");
    scanf("%[^\n]%*c", content);

    char *mail = mailHeader(sender, recepient, subject, content);
    printf("\nMail contents:\n");
    printf("***********************************************\n");
    printf("%s\n", mail);
    printf("***********************************************\n");

    bzero(buffer, 2000);
    strcpy(buffer, mail);
    send(server_sock, buffer, 2000, 0);
    printf("Mail sent\n");

    close(server_sock);
}
