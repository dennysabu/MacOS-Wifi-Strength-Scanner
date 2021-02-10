all: scanner.c scanner.h
	gcc -Werror -o scanner scanner.c

debug: scanner.c scanner.h
	gcc -Werror -g scanner.c scanner.h
clean: scanner
	rm scanner