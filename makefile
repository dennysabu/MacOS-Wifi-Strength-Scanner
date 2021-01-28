all: scanner.c
	gcc -Werror -o scanner scanner.c
clean: scanner
	rm scanner