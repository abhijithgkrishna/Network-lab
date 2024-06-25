#include<unistd.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<stdlib.h>

void main()
{
	char* ip = "127.0.0.1";
	int port = 5566;
	int server_sock, client_sock;
	struct sockaddr_in server_add, client_add;
	socklen_t addr_size;
	char buffer[1024];

	server_sock = socket(AF_INET, SOCK_STREAM,0);
	printf("%d \n",server_sock );
}