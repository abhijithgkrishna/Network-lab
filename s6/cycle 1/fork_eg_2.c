/*
	Write a C program to create a child process using fork system call.
	The parent process reads a text from a file and prints it.
*/

#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
void main()
{
	int pid, fd, n;
	char buff[100];
	pid_t id1, id2, id3;
	pid = fork();
	if (pid < 0)
	{
		printf("fork failed\n");
		exit(0);
	}
	else if (pid == 0)
	{
		printf("In child process \n");
		id1 = getpid();
		id2 = getppid();
		printf("Child id = %d, parent id = %d \n", id1, id2);

		fd = open("source.txt", O_RDONLY, 0664);
		n = read(fd, buff, 100);
		buff[n] = '\0';
		printf("Text read is : %s\n", buff);
		close(fd);
	}
	else
	{
		wait(NULL);
		id3 = getpid();
		printf("The return value of fork is %d", pid);
		printf("pid of parent process  = %d \n", id3);
	}
}
