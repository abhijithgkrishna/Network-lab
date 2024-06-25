/*
	Write a C program to copy the contents of one file to another file.
*/

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

void main()
{
	int fd1, fd2;
	int n1, n2;
	char buf[50];

	fd1 = open("./files/source.txt", O_RDONLY, 0777);

	n1 = read(fd1, buf, 50);
	fd2 = open("./files/dest.txt", O_CREAT | O_WRONLY | O_TRUNC, 0777);
	n2 = write(fd2, buf, n1);

	printf("Number of bytes written from source.txt to dest.txt : %d  \n", n2);
	close(fd1);
	close(fd2);
}