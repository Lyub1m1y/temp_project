all: s21_cat

s21_cat:
	gcc -Wall -Werror -Wextra -c s21_cat.c
	gcc s21_cat.o -o s21_cat
	rm -rf *.o

rebuild: clean all

clean:
	rm -rf *.o s21_cat