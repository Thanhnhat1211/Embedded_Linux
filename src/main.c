#include <stdio.h>
#include "strutils.h"

int main(){
    char name[50] = " Xin chao cac ban ";
    int number_result;

    printf("Chuoi ban dau: '%s'\n", name);
    str_trim(name); 
    printf("Chuoi sau khi trim: '%s'\n", name);

    printf("Chuoi khi chua reverse: '%s'\n", name);
    str_reverse(name); 
    printf("Chuoi sau khi reverse: '%s'\n", name);

    char number_str[] = "12345";
    if (str_to_int(number_str, &number_result)) {
        printf("Chuoi '%s' chuyen doi sang int la: %d\n", number_str, number_result);
    } else {
        printf("Khong the chuyen doi chuoi '%s' sang int.\n", number_str);
    }
    return 0;
}