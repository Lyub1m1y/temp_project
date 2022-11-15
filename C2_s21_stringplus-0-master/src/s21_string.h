#ifndef SRC_S21_STRING_H_
#define SRC_S21_STRING_H_

#include <stdio.h>
#include <string.h>

#define s21_size_t unsigned long
#define s21_NULL (void*)0

s21_size_t s21_strlen(const char* str);

int s21_strcmp(char* str_1, char* str_2);

int s21_strncmp(char* str_1, char* str_2, s21_size_t n);

int s21_memcmp(const void* str_1, const void* str_2, s21_size_t n);

char* s21_strcpy(char* dest, const char* src);

char* s21_strncpy(char* dest, const char* src, size_t n);

// char* s21_strcat(char* __s1, const char* __s2);

#endif  // SRC_S21_STRING_H_
