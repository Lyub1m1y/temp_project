#include "s21_cat.h"

#include <getopt.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
  const char *short_options = "b::e::n::s::t::v::";
  const struct option long_options[] = {
      {"nonblank", no_argument, NULL, 'b'},
      {"endofline", no_argument, NULL, 'e'},
      {"number", no_argument, NULL, 'n'},
      {"squeeze-blank", no_argument, NULL, 's'},
      {"tabs", no_argument, NULL, 't'},
      {"special", no_argument, NULL, 'v'},
      {NULL, 0, NULL, 0}};
  int rez, option_index = -1;
  int flag_b = 0, flag_e = 0, flag_n = 0, flag_s = 0, flag_tt = 0, flag_v = 0;
  int opt_count = 1;
  if (*argv[1] != '-' && argc > 2) {
    printOutput(argv, opt_count, flag_b, flag_e, flag_n, flag_s, flag_tt,
                flag_v);
    fprintf(stderr, "[REMINDER] Flags must be before file in input.");
    return -1;
  }
  while ((rez = getopt_long(argc, argv, short_options, long_options,
                            &option_index)) != -1) {
    switch (rez) {
      case 'b':
        opt_count++;
        flag_b = 1;
        break;
      case 'e':
        opt_count++;
        flag_e = 1;
        flag_v = 1;
        break;
      case 'n':
        opt_count++;
        flag_n = 1;
        break;
      case 's':
        opt_count++;
        flag_s = 1;
        break;
      case 't':
        opt_count++;
        flag_tt = 1;
        flag_v = 1;
        break;
      case 'v':
        opt_count++;
        flag_v = 1;
        break;
    }
    option_index = -1;
  }
  printOutput(argv, opt_count, flag_b, flag_e, flag_n, flag_s, flag_tt, flag_v);
  return 0;
}

int printOutput(char *argv[], int opt_count, int flag_b, int flag_e, int flag_n,
                int flag_s, int flag_tt, int flag_v) {
  FILE *file;
  int files_count = 1;
  file = fopen(argv[opt_count + 1], "r");
  if (file == NULL) {
    file = fopen(argv[opt_count], "r");
    if (file == NULL) {
      fprintf(stderr, "%s: No such file or directory.\n", argv[opt_count]);
      return -1;
    }
  } else {
    files_count++;
  }
  char text_buffer[128];
  int line_count = 1;
  int line_length = 0;
  int blank_count = 0;
  for (int z = 0; z < files_count; z++) {
    if (z == 0 && z < files_count) {
      fclose(file);
      file = fopen(argv[opt_count], "r");
    }
    if (z == 1 && z < files_count) {
      fclose(file);
      blank_count = 0;
      line_count = 1;
      file = fopen(argv[opt_count + 1], "r");
    }
    while (fgets(text_buffer, sizeof(text_buffer), file)) {
      line_length = strlen(text_buffer);
      if ((flag_b == 1) || (flag_n == 1 && flag_b == 1))
        countNonBlank(&line_count, text_buffer);
      if (flag_n == 1 && flag_b == 0 && blank_count <= 1) {
        countNumber(&line_count);
      }
      for (int i = 0; i < line_length; i++) {
        if (flag_s == 1 && text_buffer[0] == '\n') {
          blank_count++;
          if (blank_count <= 1 && flag_e == 0) {
            printf("%c", text_buffer[0]);
          } else {
            if (blank_count <= 1 && flag_e == 1) {
              printf("$");
              printf("\n");
            }
          }
        } else {
          blank_count = 0;
          if (flag_tt == 1 && text_buffer[i] == '\t') {
            printf("^I");
          } else {
            if (flag_e == 1 && i < line_length - 1) {
              printChar(i, text_buffer, flag_v);
            } else {
              if (flag_e == 1 && i <= line_length && blank_count <= 1 &&
                  text_buffer[i] == '\n') {
                printf("$");
                printf("\n");
              } else {
                printChar(i, text_buffer, flag_v);
              }
            }
          }
        }
      }
    }
  }
  fclose(file);
  return 0;
}

void printChar(int i, char *text_buffer, int flag_v) {
  if (flag_v == 1) {
    if ((text_buffer[i] >= 0 && text_buffer[i] < 9) ||
        (text_buffer[i] > 10 && text_buffer[i] < 32) ||
        (text_buffer[i] == 127)) {
      printf("^");
      if (text_buffer[i] == 127) {
        text_buffer[i] -= 64;
        printf("%c", text_buffer[i]);
      } else {
        text_buffer[i] += 64;
        printf("%c", text_buffer[i]);
      }
    } else {
      printf("%c", text_buffer[i]);
    }
  } else {
    printf("%c", text_buffer[i]);
  }
}

int countNumber(int *line_count) {
  if (*line_count < 10) printf("     %d	", *line_count);
  if (*line_count > 9 && *line_count < 100) printf("    %d	", *line_count);
  if (*line_count >= 100) printf("   %d	", *line_count);
  return (*line_count)++;
}

void countNonBlank(int *line_count, char *text_buffer) {
  if (text_buffer[0] != '\n') {
    if (*line_count < 10) printf("     %d	", *line_count);
    if (*line_count > 9 && *line_count < 100) printf("    %d	", *line_count);
    if (*line_count >= 100) printf("   %d	", *line_count);
    (*line_count)++;
  }
}
