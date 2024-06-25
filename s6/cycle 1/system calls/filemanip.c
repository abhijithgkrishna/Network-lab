#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>


void main()
{
	int fd;
	int n,p;
	char buf[10];
	printf("Enter data to write in file : \n");
	fd = open("fats.txt", O_CREAT | O_RDWR, 0777);
	printf("Chk fd %d ",fd);
	int cp = fd;
	n = read(0,buf,10);
	printf("Thew %d \n",n );
	write(fd,buf,n);
		printf("Chk fd %d ",fd);

	printf("Data written \n");
	char newbuf[10] = "eld";
	p = read(fd,newbuf,10);
		printf("Chk fd %d ",fd);

	printf("%d \n",p);
	printf(" hi %s \n", newbuf);
	close(fd);
}