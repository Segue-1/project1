proc_fan: proc_fan.c
	gcc -g -o proc_fan proc_fan.c -std=c99
clean:
	@echo "Cleaning up..."
	rm proc_fan
