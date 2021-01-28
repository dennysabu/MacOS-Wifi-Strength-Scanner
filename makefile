all: scanner.c
	gcc -o scanner scanner.c
clean: scanner
	rm scanner