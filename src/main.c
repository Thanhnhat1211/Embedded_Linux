#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>

int main(int argc, char *argv[]){
    if(argc != 2){
        printf("Usage: %s <file_path>\n", argv[0]);
        return 1;
    }

    struct stat st;
    if(lstat(argv[1], &st) == -1){
        perror("lstat");
        return 1;
    }

    char file_type[30];
    if(S_ISREG(st.st_mode))
        strcpy(file_type, "Regular File");
    else if(S_ISDIR(st.st_mode))
        strcpy(file_type, "Directory");
    else if(S_ISLNK(st.st_mode))
        strcpy(file_type, "Symbolic link");
    else
        strcpy(file_type, "Other");

    char last_modified[100];
    struct tm *tm_info = localtime(&st.st_mtime);
    strftime(last_modified, sizeof(last_modified), "%d-%m-%Y %H:%M:%S", tm_info);

    printf("File path      :%s\n", argv[1]);
    printf("File type      :%s\n", file_type);
    printf("Size file      :%ld\n", st.st_size);
    printf("Last modified  :%s\n", last_modified);
    return 0;
}