/* C program to implement file manipulation using system calls
   1. Read data from the user (using open call)
   2. Write the data to a file (using write call)
   3. Read the data from the file and display it
*/

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

void main()
{
	int fd;
	int n_read, n_write, n_newread;
	char buf[100], newbuf[100];

	printf("Enter data to write in file : ");
	fflush(stdout);				// To clear the output buffer
	n_read = read(0, buf, 100); // 0 is the file descriptor for standard input

	// To check if read was successful
	// printf("Number of bytes read :  %d \n", n_read);

	fd = open("./files/file-manipulation.txt", O_CREAT | O_RDWR, 0777);

	// To check if open was successful
	// printf("Check fd :  %d \n", fd);

	n_write = write(fd, buf, n_read);

	// To check if write was successful
	// printf("Number of bytes read :  %d \n", n_write);

	if (n_write == -1)
	{
		printf("Error in writing to file \n");
	}
	else
	{
		printf("Data written to file successfully \n");
	}

	lseek(fd, 0, SEEK_SET); // To move the file pointer to the beginning of the file
	n_newread = read(fd, newbuf, 100);

	// To check if read was successful
	// printf("Number of bytes read :  %d \n", n_newread);

	printf("The data in new buffer : %s", newbuf);
	close(fd);
}