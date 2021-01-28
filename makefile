all: scanner.c scanner.h
	gcc -Werror -o scanner scanner.c
clean: scanner
	rm scanner