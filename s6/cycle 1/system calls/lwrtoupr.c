#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>

void cnvrtlwr(char * str)
{
	for (int i = 0; str[i] != '\0'; ++i)
	{
		if (str[i] >= 'a' && str[i] <= 'z')
		{
			str[i] -= 32;
		}
	}
	printf("After converting to upper : %s \n",str);
}
void cnvrtupr(char * str)
{
	for (int i = 0; str[i] != '\0'; ++i)
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
		{
			str[i] += 32;
		}
	}
	printf("After converting to lower : %s \n",str);
}

void main()
{
	char mystr[10];
	printf("Enter string to convert : ");
	scanf("%s",mystr);
	int pid;
	pid = fork();

	if (pid < 0)
	{
		printf("Fork failed \n");
	}
	else if (pid == 0)
	{
		printf("Child Process \n");
		cnvrtlwr(mystr);
	}
	else
	{
		wait(NULL);
		printf("Parent Process \n");
		cnvrtupr(mystr);
	}

}