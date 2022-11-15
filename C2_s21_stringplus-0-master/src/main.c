#include "s21_string.h"

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
  //   printf("s1_strcpy = %s\n", s1);
  //   printf("s2 = %s\n", s2);
  //   s21_strcpy(s2, s1);
  //   printf("s21_strcpy: s2 = %s\n", s2);
  // Тест s21_strcpy end

  // Тест s21_strncpy
  printf("s1_strncpy = %s\n", s1);
  printf("s2 = %s\n", s2);
  s21_strncpy(s2, s1, 4);
  printf("s21_strncpy: s2 = %s\n", s2);
  // Тест s21_strncpy end
  return 0;
}
