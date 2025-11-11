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
        printf("Child process: PID=%d\n", getpid());
        printf("Child exiting now...\n");
        exit(0);  // Kết thúc ngay lập tức
    } else {
        // Tiến trình cha
        printf("Parent process: PID=%d\n", getpid());
        printf("Child PID=%d\n", pid);
        printf("Parent sleeping for 30 seconds...\n");
        sleep(30);  // Không gọi wait(), nên con sẽ trở thành zombie
        printf("Parent exiting.\n");
    }

    return 0;
}
