/****************************************
 * Author: Collin Smith
 * Description:
 * Date:
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

        char *sub_string;
        char **args = malloc(16 * sizeof(char));

        sub_string = strtok(string, " ");

        int i = 0;
        while(sub_string != NULL) {
                args[i] = malloc(16 * sizeof(char));
                args[i] = sub_string;
                sub_string = strtok(NULL, " ");
                i += 1;
        }

        args[i] = NULL;
        return args;
}


int proc_fan(int n) {
	int i;
	pid_t childpid = 0;
	int pr_count = 0;
	char command[MAX_CANON];
	char** arg_arr;
	

	while(fgets(command, MAX_CANON, stdin)) {
        	if (pr_count == n) {
		wait(NULL);
		pr_count -=1;
		}
	
	
	if((childpid = fork()) == 0) {
		strtok(command, "\n");
		arg_arr = makeargv(command);
		execvp(arg_arr[0], arg_arr);
		perror("Child failed to execvp the command");
		return 1;
	}

	if (childpid == -1) {
		perror("Child failed to fork\n");
		return 1;
	}

	pr_count += 1;

	if(waitpid(-1, NULL, WNOHANG) > 0) {
		pr_count -= 1;
	}

	if (childpid > 0) {
		while (wait(NULL) > 0);
	}
	}

	return 0;        

}

int main (int argc, char *argv[]) {
        pid_t childpid = 0;
        int i, n, option;
        int pr_count = 0;


        /*Calculate true number of arguments passed through command line. */

        if (argc != 3) {
                /* check for valid number of command-line arguments */
                fprintf(stderr, "Error: %d parameters passed.\n", argc - 1);
                printf("Please enter 1 option followed by 1 argument.\n");
		printf("Example: ./runsim.exe -n 5\n");
                return 1;
        }
	
	/*Convert char string from argv[1] to int. */
        n = atoi(argv[2]);
	
	int nflag = 0;

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
