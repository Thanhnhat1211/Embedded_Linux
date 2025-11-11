#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    } else if (pid == 0) {
        // Tiến trình con
        printf("Child started: PID=%d, PPID=%d\n", getpid(), getppid());
        for (int i = 0; i < 5; i++) {
            printf("Child running... PID=%d, PPID=%d\n", getpid(), getppid());
            sleep(2);  // Tạm dừng 2 giây
        }
        printf("Child finished.\n");
    } else {
        // Tiến trình cha
        printf("Parent process: PID=%d\n", getpid());
        printf("Parent exiting now...\n");
        exit(0);  // Cha thoát ngay lập tức
    }

    return 0;
}
