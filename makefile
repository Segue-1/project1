runsim.exe: runsim.c
	gcc -g -o runsim.exe runsim.c -std=c99
clean:
	@echo "Cleaning up..."
	rm runsim.exe
