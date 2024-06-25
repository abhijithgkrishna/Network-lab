#include<unistd.h>
#include<sys/wait.h>
#include<stdio.h>

void main()
{
	int pid;

	int a[10] = {1,2,3,4,5,6,7,8,9,0};
	int n = 10;
	int sumOdd = 0, sumEven = 0;
	printf("The array is : \n");
	for (int i = 0; i < 10; ++i)
	{
		printf("%d ", a[i]);
	}

	pid = fork();
	if (pid < 0)
	{
		printf("Bad fork");
	}
	else if (pid == 0)
	{
		for (int i = 0; i < n; ++i)
		{
			if (a[i] % 2 != 0)
			{
				sumOdd += a[i];
			}
		}
		printf("In child process \n");
		printf("Sum of odd numbers  = %d \n",sumOdd);
	}
	else
	{
		wait(NULL);
		for (int i = 0; i < n; ++i)
		{
			if (a[i] % 2 == 0)
			{
				sumEven += a[i];
			}
		}
		printf("In child process \n");
		printf("Sum of even numbers  = %d \n",sumEven);
	}

}