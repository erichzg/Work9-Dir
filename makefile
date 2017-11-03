all: dir_info.c
	gcc -o dir_info dir_info.c
run: all
	./dir_info
