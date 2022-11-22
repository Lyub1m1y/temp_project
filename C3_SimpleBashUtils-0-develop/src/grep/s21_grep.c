#include "s21_grep.h"
#include <stdlib.h>

regex_t regeex;
regmatch_t match;

int main(int argc, char *argv[]) {
  int pattern_comp;
  char e_pattern_template[128][128];
  int e_pattern_count = 0;
  char f_pattern_file[128];
  const char *short_options = "e:ivclnhsf:o";
  const struct option long_options[] = {
      {"pattern", required_argument, NULL, 'e'},
      {"icase", no_argument, NULL, 'i'},
      {"invert", no_argument, NULL, 'v'},
      {"count-exec", no_argument, NULL, 'c'},
      {"counter-files", no_argument, NULL, 'l'},
      {"line-counter", no_argument, NULL, 'n'},
      {"not-print-file", no_argument, NULL, 'h'},
      {"not-print-error", no_argument, NULL, 's'},
      {"file-pattern", required_argument, NULL, 'f'},
      {"single-word", no_argument, NULL, 'o'},
      {NULL, 0, NULL, 0}};
  int rez, option_index = -1;
  struct flag_list flags = {0};
  while ((rez = getopt_long(argc, argv, short_options, long_options,
                            &option_index)) != -1) {
    switch (rez) {
      case 'e':
        flags.flag_e = 1;
        strcpy(e_pattern_template[e_pattern_count], optarg);
        e_pattern_count++;
        break;
      case 'i':
        flags.flag_i = 1;
        break;
      case 'v':
        flags.flag_v = 1;
        break;
      case 'c':
        flags.flag_c = 1;
        break;
      case 'l':
        flags.flag_l = 1;
        break;
      case 'n':
        flags.flag_n = 1;
        break;
      case 'h':
        flags.flag_h = 1;
        break;
      case 's':
        flags.flag_s = 1;
        break;
      case 'f':
        flags.flag_f = 1;
        strcpy(f_pattern_file, optarg);
        e_pattern_count++;
        break;
      case 'o':
        flags.flag_o = 1;
        break;
    }
    option_index = -1;
  }
  fileCounter(argv, flags, argc, &pattern_comp, e_pattern_template,
              e_pattern_count, f_pattern_file);
  return 0;
}

int fileCounter(char *argv[], struct flag_list flags, int argc,
                int *pattern_comp, char e_pattern_template[128][128],
                int e_pattern_count, char f_pattern_file[128]) {
  char file_name[128];
  char file_arg[128][128];
  char pattern_file_buffer[128];
  int current_line = 0;
  if (flags.flag_f == 1) {
    FILE *pattern_file;
    pattern_file = fopen(f_pattern_file, "r");
    while (
        fgets(pattern_file_buffer, sizeof(pattern_file_buffer), pattern_file)) {
      for (int k = 0; k < 128; k++) {
        if (pattern_file_buffer[k] == '\n') break;
        file_arg[current_line][k] = pattern_file_buffer[k];
      }
      current_line++;
    }
    fclose(pattern_file);
  }
  if (flags.flag_e == 0 && flags.flag_f == 0) {
    for (int i = optind + 1; i < argc; i++) {
      strcpy(file_name, argv[i]);
      printLines(argv, flags, file_name, argc, current_line, file_arg,
                 e_pattern_count, e_pattern_template, pattern_comp);
    }
  } else {
    for (int i = optind; i < argc; i++) {
      strcpy(file_name, argv[i]);
      printLines(argv, flags, file_name, argc, current_line, file_arg,
                 e_pattern_count, e_pattern_template, pattern_comp);
    }
  }
  return 0;
}

int printLines(char *argv[], struct flag_list flags, char *file_name, int argc,
               int current_line, char file_arg[128][128], int e_pattern_count,
               char e_pattern_template[128][128], int *pattern_comp) {
  int f_sum_check = 0;
  if (flags.flag_e == 0)
    f_sum_check = argc - optind;
  else
    f_sum_check = argc - optind + 1;
  int print_line_number;
  print_line_number = 1;
  int line_success = 0;
  int line_success_invert = 0;
  FILE *file;
  file = fopen(file_name, "r");
  if (file == NULL) {
    if (flags.flag_s == 0) fprintf(stderr, "No such file or directory.\n");
    return -1;
  }
  char text_buffer[1280];
  int need_print = 0;
  if (flags.flag_h == 1) f_sum_check = 2;
  while (fgets(text_buffer, sizeof(text_buffer), file)) {
    patternCheck(argv, flags, f_sum_check, print_line_number, file_name,
                 text_buffer, current_line, e_pattern_count, pattern_comp,
                 file_arg, e_pattern_template, &line_success,
                 &line_success_invert, &need_print);
    need_print = 0;
    print_line_number++;
  }
  if (flags.flag_l == 1 && flags.flag_c == 1) {
    if (f_sum_check > 2) {
      if (flags.flag_v == 0) {
        if (line_success == 0) {
          if (flags.flag_h == 0)
            printf("%s:0\n", file_name);
          else
            printf("0\n");
        } else {
          printf("%s:1\n", file_name);
          printf("%s\n", file_name);
        }
      } else {
        if (line_success_invert == 0) {
          if (flags.flag_h == 0)
            printf("%s:0\n", file_name);
          else
            printf("0\n");
        } else {
          printf("%s:1\n", file_name);
          printf("%s\n", file_name);
        }
      }
    } else {
      if (flags.flag_v == 0) {
        if (line_success == 0) {
          if (flags.flag_h == 0)
            printf("%s:0\n", file_name);
          else
            printf("0\n");
        }
        if (line_success >= 1) {
          printf("1\n%s\n", file_name);
        }
      } else {
        if (line_success_invert == 0) {
          if (flags.flag_h == 0)
            printf("%s:0\n", file_name);
          else
            printf("0\n");
        }
        if (line_success_invert >= 1) {
          printf("1\n%s\n", file_name);
        }
      }
    }
  }
  if (flags.flag_l == 1 && flags.flag_c == 0 && line_success > 0)
    printf("%s\n", file_name);
  if (flags.flag_l == 1 && flags.flag_c == 0 && flags.flag_v == 1 &&
      line_success == 0)
    printf("%s\n", file_name);
  if (flags.flag_c == 1 && flags.flag_l == 0 && f_sum_check == 2) {
    if (flags.flag_v == 0)
      printf("%d\n", line_success);
    else
      printf("%d\n", line_success_invert);
  }
  if (flags.flag_c == 1 && flags.flag_l == 0 && f_sum_check > 2) {
    if (flags.flag_v == 0)
      printf("%s:%d\n", file_name, line_success);
    else
      printf("%s:%d\n", file_name, line_success_invert);
  }
  fclose(file);
  return 0;
}

int patternCheck(char *argv[], struct flag_list flags, int f_sum_check,
                 int print_line_number, char *file_name, char *text_buffer,
                 int current_line, int e_pattern_count, int *pattern_comp,
                 char file_arg[128][128], char e_pattern_template[128][128],
                 int *line_success, int *line_success_invert, int *need_print) {
  char string_compare[1024];
  int current_line_comp = 0;
  if (flags.flag_f == 1) {
    for (int i = 0; i < current_line; i++) {
      *pattern_comp = regcomp(&regeex, file_arg[i], REG_EXTENDED);
      *pattern_comp = regexec(&regeex, text_buffer, 0, NULL, 0);
      regfree(&regeex);
      free(&regeex);
      if (*pattern_comp == 0) (*need_print)++;
      if (flags.flag_v == 0 && *need_print >= 1) {
        if ((strcmp(string_compare, text_buffer) != 0) ||
            (current_line_comp != print_line_number)) {
          flagWork(f_sum_check, flags, print_line_number, file_name,
                   pattern_comp, text_buffer, line_success, line_success_invert,
                   e_pattern_count, e_pattern_template);
          strcpy(string_compare, text_buffer);
          current_line_comp = print_line_number;
        }
      }
    }
  }
  if (flags.flag_e == 1) {
    for (int i = 0; i < e_pattern_count; i++) {
      if (flags.flag_i == 0) {
        *pattern_comp = regcomp(&regeex, e_pattern_template[i], REG_EXTENDED);
        *pattern_comp = regexec(&regeex, text_buffer, 0, NULL, 0);
        regfree(&regeex);
        free(&regeex);
        if (*pattern_comp == 0) (*need_print)++;
        if (flags.flag_v == 0 && *need_print >= 1) {
          if ((strcmp(string_compare, text_buffer) != 0) ||
              (current_line_comp != print_line_number)) {
            flagWork(f_sum_check, flags, print_line_number, file_name,
                     pattern_comp, text_buffer, line_success,
                     line_success_invert, e_pattern_count, e_pattern_template);
            strcpy(string_compare, text_buffer);
            current_line_comp = print_line_number;
          }
        }
      } else {
        *pattern_comp = regcomp(&regeex, e_pattern_template[i], REG_ICASE);
        *pattern_comp = regexec(&regeex, text_buffer, 0, NULL, 0);
        regfree(&regeex);
        free(&regeex);
        if (*pattern_comp == 0) (*need_print)++;
        if (flags.flag_v == 0 && *need_print == 1) {
          flagWork(f_sum_check, flags, print_line_number, file_name,
                   pattern_comp, text_buffer, line_success, line_success_invert,
                   e_pattern_count, e_pattern_template);
        }
      }
    }
    if ((flags.flag_v == 1 && *need_print == 0))
      flagWork(f_sum_check, flags, print_line_number, file_name, pattern_comp,
               text_buffer, line_success, line_success_invert, e_pattern_count,
               e_pattern_template);
  }
  if (flags.flag_e == 0 && flags.flag_f == 0) {
    if (flags.flag_i == 1 && flags.flag_e == 0) {
      *pattern_comp = regcomp(&regeex, argv[optind], REG_ICASE);
      flagWork(f_sum_check, flags, print_line_number, file_name, pattern_comp,
               text_buffer, line_success, line_success_invert, e_pattern_count,
               e_pattern_template);
      regfree(&regeex);
      free(&regeex);
    }
    if (flags.flag_e == 0 && flags.flag_i == 0) {
      *pattern_comp = regcomp(&regeex, argv[optind], REG_EXTENDED);
      flagWork(f_sum_check, flags, print_line_number, file_name, pattern_comp,
               text_buffer, line_success, line_success_invert, e_pattern_count,
               e_pattern_template);
      regfree(&regeex);
      free(&regeex);
    }
  }
  return 0;
}

int flagWork(int f_sum_check, struct flag_list flags, int print_line_number,
             char *file_name, int *pattern_comp, char *text_buffer,
             int *line_success, int *line_success_invert, int e_pattern_count,
             char e_pattern_template[128][128]) {
  int offset = 0;
  int length = strlen(text_buffer);
  int flag_duplicate = 0;
  if (flags.flag_o == 1 && flags.flag_v == 0) {
    if (flags.flag_e == 1 && flags.flag_f == 0) {
      for (int i = 0; i < e_pattern_count; i++) {
        if (flags.flag_i == 0)
          *pattern_comp = regcomp(&regeex, e_pattern_template[i], REG_EXTENDED);
        else
          *pattern_comp = regcomp(&regeex, e_pattern_template[i], REG_ICASE);
        while (!regexec(&regeex, text_buffer + offset, 1, &match, 0)) {
          if (flags.flag_c == 0 && flags.flag_l == 0 && flag_duplicate == 0) {
            if (flags.flag_h == 1 || f_sum_check == 2) {
              if (flags.flag_n == 1) printf("%d:", print_line_number);
            } else {
              if (flags.flag_n == 1)
                printf("%s:%d:", file_name, print_line_number);
              else
                printf("%s:", file_name);
            }
          }
          for (int i = offset + match.rm_so; i < offset + match.rm_eo; i++) {
            if (flags.flag_c == 0 && flags.flag_l == 0)
              printf("%c", text_buffer[i]);
          }
          if (flags.flag_c == 0 && flags.flag_l == 0) printf("\n");
          if ((flags.flag_c == 1 || flags.flag_l == 1) && flag_duplicate == 0)
            (*line_success)++;
          offset += match.rm_eo;
          flag_duplicate = 1;
        }
        regfree(&regeex);
        free(&regeex);
      }
    } else {
      while (!regexec(&regeex, text_buffer + offset, 1, &match, 0)) {
        if (flags.flag_c == 0 && flags.flag_l == 0 && flag_duplicate == 0) {
          if (flags.flag_h == 1 || f_sum_check == 2) {
            if (flags.flag_n == 1) printf("%d:", print_line_number);
          } else {
            if (flags.flag_n == 1)
              printf("%s:%d:", file_name, print_line_number);
            else
              printf("%s:", file_name);
          }
        }
        for (int i = offset + match.rm_so; i < offset + match.rm_eo; i++) {
          if (flags.flag_c == 0 && flags.flag_l == 0) {
            printf("%c", text_buffer[i]);
          }
        }
        if (flags.flag_c == 0 && flags.flag_l == 0) printf("\n");
        if ((flags.flag_c == 1 || flags.flag_l == 1) && flag_duplicate == 0)
          (*line_success)++;
        offset += match.rm_eo;
        flag_duplicate = 1;
      }
      regfree(&regeex);
      free(&regeex);
    }
    flag_duplicate = 0;
    *line_success_invert = print_line_number - *line_success;
  } else {
    *pattern_comp = regexec(&regeex, text_buffer, 0, NULL, 0);
    if (*pattern_comp == 0) {
      if (flags.flag_c == 1 || flags.flag_l == 1) (*line_success)++;
      if (flags.flag_n == 1 && flags.flag_v == 0 && flags.flag_c == 0 &&
          f_sum_check == 2 && flags.flag_l == 0)
        printf("%d:", print_line_number);
      if (flags.flag_l == 0 && flags.flag_c == 0 && flags.flag_v == 0) {
        if (f_sum_check == 2) {
          if (text_buffer[length - 1] == '\n' && text_buffer[length] != '\n')
            printf("%s", text_buffer);
          else
            printf("%s\n", text_buffer);
        }
        if (f_sum_check > 2) {
          if (flags.flag_n == 1 && flags.flag_v == 0) {
            if (text_buffer[length - 1] == '\n' && text_buffer[length] != '\n')
              printf("%s:%d:%s", file_name, print_line_number, text_buffer);
            else
              printf("%s:%d:%s\n", file_name, print_line_number, text_buffer);
          } else {
            if (text_buffer[length - 1] == '\n' && text_buffer[length] != '\n')
              printf("%s:%s", file_name, text_buffer);
            else
              printf("%s:%s\n", file_name, text_buffer);
          }
        }
      }
    } else {
      (*line_success_invert)++;
      if (flags.flag_v == 1 && flags.flag_l == 0 && flags.flag_c == 0) {
        if (f_sum_check == 2) {
          if (text_buffer[length - 1] == '\n' && text_buffer[length] != '\n') {
            if (flags.flag_n == 1) printf("%d:", print_line_number);
            printf("%s", text_buffer);
          } else {
            if (flags.flag_n == 1) printf("%d:", print_line_number);
            printf("%s\n", text_buffer);
          }
        }
        if (f_sum_check > 2) {
          if (text_buffer[length - 1] == '\n' && text_buffer[length] != '\n') {
            if (flags.flag_n == 1)
              printf("%s:%d:%s", file_name, print_line_number, text_buffer);
            else
              printf("%s:%s", file_name, text_buffer);
          } else {
            if (flags.flag_n == 1)
              printf("%s:%d:%s\n", file_name, print_line_number, text_buffer);
            else
              printf("%s:%s\n", file_name, text_buffer);
          }
        }
      }
    }
    regfree(&regeex);
    free(&regeex);
  }
  return 0;
}
