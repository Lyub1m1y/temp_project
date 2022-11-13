#include <stdio.h>
#include <string.h>

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

int s21_memcmp(const void* str_1, const void* str_2, s21_size_t n) {
  char* i_1 = (char*)str_1;
  char* i_2 = (char*)str_2;
  int status_cmp = 0;
  int flag_exit = 0;
  if (str_1 == str_2) {
    flag_exit = 1;
  }
  for (; n > 0 && flag_exit != 1; n--) {
    if ((*i_1) != (*i_2)) {
      status_cmp = (*i_1) - (*i_2);
      flag_exit = 1;
    }
    n--;
    i_1++;
    i_2++;
  }
  return status_cmp;
}

char* s21_strcpy(char* dest, const char* src) {
  if (dest != NULL) {
    while (*src != '\0') {
      *dest = *src;
      dest++;
      src++;
    }
    *dest = '\0';
  }
  return dest;
}

// char* s21_strcat(char* __s1, const char* __s2) { return __s1; }

int main() {
  char* str_1 = "5opka";
  char* str_2 = "5opkas";
  s21_size_t n = 5;
  printf("strlen = %ld\n", s21_strlen(str_1));
  printf("strcmp = %d\n", s21_strcmp(str_1, str_2));
  printf("strncmp = %d\n", s21_strncmp(str_1, str_2, n));
  // Тест s21_memcmp
  int res = 0;
  char s1[15] = "Hello";
  char s2[15] = "Aticleworld";
  res = memcmp(s1, s2, n);
  printf("memcmp = %d\n", res);
  res = s21_memcmp(s1, s2, n);
  printf("s21_memcmp = %d\n", res);
  if (res > 0) {
    printf("s2 is less than s1\n");
  } else if (res < 0) {
    printf("s1 is less than s2\n");
  } else {
    printf("s1 is equal to s2\n");
  }
  // Тест s21_memcmp end

  // Тест s21_strcpy
  printf("s1_strcpy = %s\n", s1);
  printf("s2 = %s\n", s2);
  s21_strcpy(s2, s1);
  printf("s21_strcpy: s2 = %s\n", s2);
  // Тест s21_strcpy end
  return 0;
}