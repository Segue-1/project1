/****************************************
 * Author: Collin Smith
 * Description:
 * Date:
 * ****************************************/

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

void proc_fan(int n) {
	int i;
	pid_t childpid = 0;
	
        for (i = 1; i < n; i++) {
                if ((childpid = fork()) <= 0){
                        break;
                }
        }
        fprintf(stderr, "i:%d process ID:%ld parent ID:%ld child ID:%ld\n",
                i, (long)getpid(), (long)getppid(), (long)childpid);

}

int main (int argc, char *argv[]) {
        pid_t childpid = 0;
        int i, n, pr_limit, option;
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
        pr_limit = atoi(argv[2]);
	
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
								
				proc_fan(pr_limit);
				break;
			default:
				fprintf(stderr, "-n is only valid option.\n", argv[0]);
                   		exit(EXIT_FAILURE);
                }
	}
	return 0;
}
