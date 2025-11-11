#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

int main(){
    int a = 0;
    int ret_val;
    int status;
    ret_val = fork();
    if(0 == ret_val){
        printf("gia tri cua a: %d\n", a);
        printf("PID_Child: %d, PID_Parent: %d\n", getpid(), getppid());
        exit(10);
    }
    else if (ret_val > 0){
        printf("Gia tri cua a: %d\n", ++a);
        printf("PID: %d, PID_Parent: %d\n", getpid(), getppid());
        wait(&status);
        if(WIFEXITED(status)){
            printf("Child exited normally with status %d\n", WEXITSTATUS(status));
        } else{
            printf("Child did not exit normally\n");
        }
    }
    return 0;
}