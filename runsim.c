/****************************************
 * Author: Collin Smith
 * Description: A program that runs other programs.  Currently it only runs the programs that are passed to it.  
 * Example: ./runsim.exe -n 5 < testing.data
 * This will just run the programs and arguments listed in testing data.
 * Date: 9/22/2020
 * ****************************************/

#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <limits.h>
#include <err.h>
#include <ctype.h>
#include <string.h>
#include <stddef.h>
#define MAX_CANON 255



char **makeargv (char *string) {
	/*This function returns an array with arguments*/
        char *sub_string;
        char **args = malloc(16 * sizeof(char));
	int i = 0;
	
	/*Remove spaces */
        sub_string = strtok(string, " ");
    	
        while(sub_string != NULL) {
                args[i] = malloc(16 * sizeof(char));
                args[i] = sub_string;
                sub_string = strtok(NULL, " ");
                i += 1;
        }
	/*Add NULL to end of string. */
        args[i] = NULL;
        return args;
}


void proc_fan(int n) {
	pid_t childpid = 0;
	int pr_count = 0;
	char command[MAX_CANON];
	char** arg_arr;
	
	/*Read from stdin until EOF */
	while(fgets(command, MAX_CANON, stdin)) {
        	/*If pr_count is pr_limit(which is n), then wait for child to finish and decrement count. */
		if (pr_count == n) {
			wait(NULL);
			pr_count -=1;
		}
	
		/*Call fork, if child then execute arg[0], name of program to run. */
		if((childpid = fork()) == 0) {
			/*Get rid of \n */
			strtok(command, "\n");
			/*Get argument from makeargv. */
			arg_arr = makeargv(command);
			/*Execute, arg_arr[0] is name and arg_arr is argument. */
			execvp(arg_arr[0], arg_arr);
			perror("Execvp failed!");
			exit(0);
		}
		/*If fork failed use perror. */
		if (childpid == -1) {
			perror("Fork failed!\n");
			exit(0);
		}
		/*Wait for children to finish. */
		if (childpid > 0) {
			while (wait(NULL) > 0);
		}

	pr_count+= 1;
	}
}

int main (int argc, char *argv[]) {
        pid_t childpid = 0;
        int i, n, option;
        int pr_count = 0;

	/*Check for valid number of command line arguments. */
        if (argc != 3) {
                fprintf(stderr, "Error: %d parameters passed.\n", argc - 1);
                printf("Please enter 1 option followed by 1 argument.\n");
		printf("Example: ./runsim.exe -n 5\n");
                return 1;
        }
	
	/*Convert char string from argv[1] to int. */
        n = atoi(argv[2]);
	
	/*nflag is used to make sure multiple options are entered twice. */
	int nflag = 0;
	
	/*Get options, only n is valid, make sure only 1 is entered, if so call proc_fan(). */
        while ((option = getopt(argc, argv, "n")) != -1){
                switch (option) {
                        case 'n' :
				if (nflag) {
					printf("Only one option allowed\n");
					exit(1);
				}
				
				else {
					nflag++;
				}
								
				proc_fan(n);
				break;
			default:
				fprintf(stderr, "-n is only valid option.\n", argv[0]);
                   		exit(EXIT_FAILURE);
                }
	}
	return 0;
}
