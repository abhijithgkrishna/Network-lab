#include<stdio.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<unistd.h>
void main()
{
	int pid,f,n;
	char buff[100];
	pid_t id1, id2, id3;
	pid=fork();
	if(pid < 0)
	{
		printf("fork failed\n");
		exit(0);
	}
	else if(pid==0)
	{
		printf("Child : \n");
		id1 = getpid();
		id2 = getppid();
		printf("Child id = %d, parent id = %d \n",id1, id2 );
		f=open("source.txt",O_RDONLY,0664);
		n=read(f,buff,100);
		buff[n]='\0';
		printf("Text read is : %s\n",buff);
		close(f);
		
	}
	else{
		wait(NULL);
		id3 = getpid();
		printf("%d hello", pid);
		printf("Parent : pid = %d \n",id3 );


	}
}


