#include <stdio.h>
#include <stdlib.h>
int main (int argc, char *argv[]) {        
	int n, m;

	if (argc != 3) {
	
	printf("Enter 2 argument, integers only\n");
	exit(0);
	}

	n = atoi(argv[1]);
	m = atoi(argv[2]);

	printf("First arg: %d Second arg: %d \n", n, m);
	
	
        return 0;
}

