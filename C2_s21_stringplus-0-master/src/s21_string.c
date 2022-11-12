#include <stdio.h>

#define s21_size_t unsigned long
#define s21_NULL (void*)0

s21_size_t s21_strlen(const char* str) {
  s21_size_t length = 0;
  for (; *(str + length); length++)
    ;
  return length;
}

int s21_strcmp(char* str_1, char* str_2) {
  for (; (*str_1) && (*str_1) == (*str_2); str_1++, str_2++)
    ;
  return (*str_1) - (*str_2);
}

int s21_strncmp(char* str_1, char* str_2, s21_size_t n) {
  for (s21_size_t i = 0; (*str_1) && (*str_1) == (*str_2) && i < n - 1;
       str_1++, str_2++, i++)
    ;
  return (*str_1) - (*str_2);
}

int main() {
  char* str_1 = "5opka";
  char* str_2 = "5opkas";
  s21_size_t n = 5;
  printf("strlen = %ld\n", s21_strlen(str_1));
  printf("strcmp = %d\n", s21_strcmp(str_1, str_2));
  printf("strncmp = %d\n", s21_strncmp(str_1, str_2, n));
  return 0;
}