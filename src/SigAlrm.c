#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int counter = 0;

void timer_handler(int sig) {
    counter++;
    printf("Timer: %d seconds\n", counter);

    if (counter >= 10) {
        printf("Timer finished. Exiting...\n");
        exit(0);
    }

    // Đặt bộ hẹn giờ lại để kích hoạt sau 1 giây nữa
    alarm(1);
}

int main() {
    // Đăng ký hàm xử lý cho tín hiệu SIGALRM
    signal(SIGALRM, timer_handler);

    // Đặt báo thức đầu tiên sau 1 giây
    alarm(1);

    // Giữ chương trình chạy
    while (1) {
        pause();  // Chờ tín hiệu
    }

    return 0;
}
