#ifndef s21_grep
#define s21_grep

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <string.h>

struct flag_list {
  int flag_e;
  int flag_i;
  int flag_v;
  int flag_c;
  int flag_l;
  int flag_n;
  int flag_h;
  int flag_s;
  int flag_f;
  int flag_o;
};

int fileCounter(char *argv[], struct flag_list flags, int argc,
                int *pattern_comp, char e_pattern_template[128][128],
                int e_pattern_count, char f_pattern_file[128]);
int printLines(char *argv[], struct flag_list flags, char *file_name, int argc,
               int current_line, char file_arg[128][128], int e_pattern_count,
               char e_pattern_template[128][128], int *pattern_comp);
int patternCheck(char *argv[], struct flag_list flags, int f_sum_check,
                 int print_line_number, char *file_name, char *text_buffer,
                 int current_line, int e_pattern_count, int *pattern_comp,
                 char file_arg[128][128], char e_pattern_template[128][128],
                 int *line_success, int *line_success_invert, int *need_print);
int flagWork(int f_sum_check, struct flag_list flags, int print_line_number,
             char *file_name, int *pattern_comp, char *text_buffer,
             int *line_success, int *line_success_invert, int e_pattern_count,
             char e_pattern_template[128][128]);

#endif