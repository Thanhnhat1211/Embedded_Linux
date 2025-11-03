#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "strutils.h"

void str_reverse(char *str){
    int right = strlen(str) - 1;
    int left = 0;
    while(left < right){
        char temp = str[left];
        str[left] = str[right];
        str[right] = temp;
        left++;
        right--;
    }
}

void str_trim(char *str) {
    int start = 0, end, i;
    if (str == NULL) return;
    while (isspace((unsigned char)str[start])) {
        start++;
    }
    if (str[start] == '\0') {
        str[0] = '\0';
        return;
    }
    end = strlen(str) - 1;
    while (end >= start && isspace((unsigned char)str[end])) {
        end--;
    }
    for (i = 0; i <= (end - start); i++) {
        str[i] = str[start + i];
    }
    str[i] = '\0';
}

int str_to_int(const char *str, int *out) {
    if (str == NULL || *str == '\0') {
        return 0; // lỗi: chuỗi trống
    }
    char *endptr;
    errno = 0;
    long val = strtol(str, &endptr, 10); // base 10

    if (errno == ERANGE || val > INT_MAX || val < INT_MIN)
        return 0; // tràn
    if (*endptr != '\0')
        return 0; // chứa ký tự không hợp lệ

    *out = (int)val;
    return 1; // thành công
}