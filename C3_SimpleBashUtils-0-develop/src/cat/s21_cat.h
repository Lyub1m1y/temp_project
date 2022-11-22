#ifndef s21_cat
#define s21_cat

int countNumber(int *line_count);
int printOutput(char *argv[], int opt_count, int flag_b, int flag_e, int flag_n,
                int flag_s, int flag_tt, int flag_v);
void countNonBlank(int *line_count, char *text_buffer);
void printChar(int i, char *text_buffer, int flag_v);

#endif
