/*
	Program to convert a string to lower case in child process and to upper case in parent process
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

void convert_to_upper(char *str)
{
	for (int i = 0; str[i] != '\0'; ++i)
	{
		if (str[i] >= 'a' && str[i] <= 'z')
		{
			str[i] -= 32;
		}
	}
	printf("After converting to upper : %s \n", str);
}
void convert_to_lower(char *str)
{
	for (int i = 0; str[i] != '\0'; ++i)
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
		{
			str[i] += 32;
		}
	}
	printf("After converting to lower : %s \n", str);
}

void main()
{
	char mystr[10];
	printf("The child process converts string to lower case and the parent process converts string to upper case \n");
	printf("Enter string to convert : ");
	scanf("%s", mystr);
	int pid;
	pid = fork();

	if (pid < 0)
	{
		printf("Fork failed \n");
	}
	else if (pid == 0)
	{
		printf("Child Process \n");
		convert_to_lower(mystr);
	}
	else
	{
		wait(NULL);
		printf("Parent Process \n");
		convert_to_upper(mystr);
	}
}