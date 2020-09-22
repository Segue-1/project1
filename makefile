all: runsim.exe testsim.exe

runsim.exe: runsim.c
	gcc -g -o runsim.exe runsim.c -std=c99
testsim.exe: testsim.c
	gcc -g -o testsim.exe testsim.c -std=c99
clean:
	@echo "Cleaning up..."
	rm runsim.exe
	rm testsim.exe

