/****************************************
Author: Collin Smith
Description:
Date:
****************************************/

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main (int argc, char *argv[]) {
	pid_t childpid = 0;
 	int i, n, pr_limit;
	int pr_count = 0;

	/*Convert char string from argv[1] to int. */
	n = atoi(argv[1]);
	pr_limit = atoi(argv[1]);
	/*Calculate true number of arguments passed through command line. */
	
 	if ((argc - 1) != 1) { 
	/* check for valid number of command-line arguments */
 	fprintf(stderr, "Error: %d arguments entered.\n", argc);
	printf("Please enter 1 argument.\n");
 	return 1;
 	}


 	for (i = 1; i < n; i++) {
 		if ((childpid = fork()) <= 0){
 			break;
		}
	}
 	fprintf(stderr, "i:%d process ID:%ld parent ID:%ld child ID:%ld\n",
 		i, (long)getpid(), (long)getppid(), (long)childpid);
 	return 0;
}
