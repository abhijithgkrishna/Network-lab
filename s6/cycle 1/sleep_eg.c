/*
	Program to print "Hello World" 5 times with a delay of 1 second between each print.
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void main()
{
	int i = 0;
	while (i < 5)
	{
		printf("Hello World \n");
		i++;
		sleep(1);
	}
}