/*
	Write a C program to check whether a given number is prime or not using fork() system call.
	The parent process should wait for the child process to complete and then display the result.
	The check for prime number should be done in the parent process.
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int primeornot(int a) // Function to check if a number is prime or not
{
	int i;
	if (a == 1 || a == 0)
		return 1;
	for (i = 2; i < a; i++)
	{
		if (a % i == 0)
			return 1;
	}
	return 0;
}
void main()
{
	int pid = fork();
	int number, status;
	int flag = 0;
	if (pid == 0)
	{
		printf("In child process \n");
	}
	else
	{
		wait(&status);
		printf("In parent process \n");
		printf(" Enter a number :");
		scanf("%d", &number);
		if (primeornot(number) == 0)
		{
			printf("The number is prime \n");
		}
		else
			printf("The number is not prime \n");
	}
}