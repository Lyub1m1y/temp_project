#include "s21_string.h"

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
  for (; n > 0 && flag_exit != 1; n--, i_1++, i_2++) {
    if ((*i_1) != (*i_2)) {
      status_cmp = (*i_1) - (*i_2);
      flag_exit = 1;
    }
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


char* s21_strncpy(char* dest, const char* src, s21_size_t n) {
  if (dest != NULL) {
    for (s21_size_t i = 0; *src != '\0' && i < n; i++) {
      *dest = *src;
      dest++;
      src++;
    }
    *dest = '\0';
  }
  return dest;
}

// char* s21_strcat(char* __s1, const char* __s2) { return __s1; }
