FLAGS = -Wall -Werror -Wextra -std=c11 -pedantic

all: s21_string

s21_string:
	gcc $(FLAGS) main.c s21_string.c -o s21_string

rebuild:
	make clean 
	make s21_string

clean: 	
	rm -rf s21_string

