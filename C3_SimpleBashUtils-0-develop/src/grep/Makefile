all: s21_grep

s21_grep:
	gcc -Wall -Werror -Wextra -c s21_grep.c
	gcc s21_grep.o -o s21_grep
	rm -rf *.o

clean:
	rm -rf *.o s21_grep

rebuild: clean all
