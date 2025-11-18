#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/select.h>

volatile sig_atomic_t sigint_flag = 0;
volatile sig_atomic_t sigterm_flag = 0;

void signal_handler(int sig) {
    if (sig == SIGINT) {
        sigint_flag = 1;
    }
    else if (sig == SIGTERM) {
        sigterm_flag = 1;
    }
}

int main() {
    // Đăng ký xử lý tín hiệu
    signal(SIGINT,  signal_handler);
    signal(SIGTERM, signal_handler);

    printf("Program started.\n");
    printf("PID: %d\n\n", getpid());

    printf("Hướng dẫn:\n");
    printf("- Nhấn Ctrl+C để gửi SIGINT.\n");
    printf("- Ở terminal khác chạy: kill -TERM %d để gửi SIGTERM.\n", getpid());
    printf("- Nhập text và nhấn Enter để in lại dòng bạn nhập.\n\n");

    char buf[256];

    while (1) {
        // kiểm tra tín hiệu trước
        if (sigterm_flag) {
            printf("SIGTERM received. Exiting...\n");
            break;
        }

        if (sigint_flag) {
            printf("SIGINT received.\n");
            sigint_flag = 0;
        }

        // Chuẩn bị select
        fd_set readfds;
        FD_ZERO(&readfds);
        FD_SET(STDIN_FILENO, &readfds);

        struct timeval tv;
        tv.tv_sec = 1;
        tv.tv_usec = 0;

        int ret = select(STDIN_FILENO + 1, &readfds, NULL, NULL, &tv);

        if (ret < 0) {
            // select bị gián đoạn bởi signal
            continue;
        }

        if (ret == 0) {
            // timeout, không có input
            continue;
        }

        if (FD_ISSET(STDIN_FILENO, &readfds)) {
            if (fgets(buf, sizeof(buf), stdin) != NULL) {
                buf[strcspn(buf, "\n")] = '\0';
                printf("You entered: %s\n", buf);
            } else {
                printf("EOF detected. Exiting...\n");
                break;
            }
        }
    }

    return 0;
}
