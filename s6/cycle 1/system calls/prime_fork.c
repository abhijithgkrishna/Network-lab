# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>

int primeornot ( int a) {
	int i ;
	if (a == 1 || a == 0)
		return 1;
	for (i =2; i < a;i ++) {
		if(a%i ==0)
		return 1;
	}
	return 0;
 }
void main () {
	 int pid = fork () ;
	 int number , status ;
	 int flag =0;
	 if( pid ==0) {
	 printf (" Child process \n") ;
	 }
	 else {
	 wait (& status );
	 printf (" Parent process \n");
	 printf (" Enter a number :");
	 scanf ("%d" ,& number ) ;
	 if( primeornot ( number ) ==0) {
	 printf ("The number is prime \n") ;
	 }
	 else
	 printf ("The number is not prime \n");
	 }
}