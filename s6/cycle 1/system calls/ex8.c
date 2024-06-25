#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>


void main()
{
	int fd, fd2;
	int n,m;
	char buf[50];
	
	fd = open("source.txt",O_RDONLY, 0777);
	
	n = read(fd,buf,50);
	fd2 = open("dest.txt",O_CREAT | O_WRONLY | O_TRUNC, 0777);
	m = write(fd2,buf,n);

	printf("Number of bytes written from source.txt to dest.txt : %d  \n", m);
	close(fd);
	close(fd2);
}