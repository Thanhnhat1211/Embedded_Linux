#ifndef STRUTILS_H
#define STRUTILS_H

#include <errno.h>
#include <limits.h>

void str_reverse(char *str);
void str_trim(char *str);
int str_to_int(const char *str, int *out);

#endif 