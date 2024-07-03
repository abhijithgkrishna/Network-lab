#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/select.h>
#include <arpa/inet.h>
#include <stdlib.h>

#define timeoutValue 5

void main()
{
  char *ip = "127.0.0.100";
  int port = 5568;

  int sockfd;
  struct sockaddr_in addr;
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

  int packetCounter = 1;

  while (packetCounter <= 3)
  {
    bzero(buffer, 1024);
    sprintf(buffer, "%d", packetCounter);
    printf("Client: Sending packet %s\n", buffer);
    sendto(sockfd, buffer, 1024, 0, (struct sockaddr *)&addr, sizeof(addr));

    bzero(buffer, 1024);
    addr_size = sizeof(addr);

    struct timeval timeout;
    timeout.tv_sec = timeoutValue;
    timeout.tv_usec = 0;

    if (setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) < 0)
      printf("Error\n");

    else
    {
      bzero(buffer, 1024);
      addr_size = sizeof(addr);

      int rec = recvfrom(sockfd, buffer, 1024, 0, (struct sockaddr *)&addr, &addr_size);
      if (rec < 0)
        printf("Client: Timeout error! Sending packet again\n");
      else
      {
        printf("Client: Received acknowledgement for packet %s\n", buffer);
        packetCounter++;
      }
    }

    sleep(1);
  }
}
