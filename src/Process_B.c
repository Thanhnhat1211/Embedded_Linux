#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    if(argc < 2){
        printf("Usage: %s <command_type>\n", argv[0]);
        return 1;
    }
    //Thiet lap bien moi truong
    setenv("MY_COMMAND", argv[1], 1);

    int ret_val;
    ret_val = fork();

    if(ret_val == 0){
        // Đọc giá trị biến môi trường và thực thi lệnh tương ứng
        const char *command = getenv("MY_COMMAND");
        if (command != NULL) {
            printf("PID_Current: %d, PID_Parent: %d\n", getpid(), getppid());
            printf("Executing command: %s\n", command);
            execlp(command, command, NULL);  // Thực thi lệnh được truyền qua biến môi trường
        } else {
            printf("MY_COMMAND environment variable is not set.\n");
            return 1;
        }     
    } else if(ret_val > 0){
        wait(NULL);
    } else{
        printf("Fork failed\n");
        return 1;
    }
    return 0;
}

