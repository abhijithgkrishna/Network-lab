/*
	Program to demonstrate fork system call
	1. Create a child process using fork
	2. Print the process id of the parent and child process
	The parent process waits for the child process to complete
*/

#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
	int pid;
	int status;
	pid = fork(); // Create a child process
	if (pid < 0)
	{
		printf("Fork unsuccessful \n");
	}
	else if (pid == 0)
	{
		printf("I am child process \n");
		printf("Child process id : %d \n", getpid());
	}
	else
	{
		wait(&status); // Wait for the child process to complete
		printf("I am parent process \n");
		printf("Parent process id : %d \n", getpid());
	}
	return 0;
}