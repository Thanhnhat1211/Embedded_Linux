#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void) {
    int pipefd[2];      // pipefd[0] = read end, pipefd[1] = write end
    pid_t pid1, pid2;

    // 1. Tạo pipe
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // 2. Tiến trình con 1: thực thi "ls -l"
    pid1 = fork();
    if (pid1 < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid1 == 0) {
        // ----- Child 1 -----
        // Gửi dữ liệu vào đầu ghi của pipe
        // stdout -> pipefd[1]

        // Không dùng đầu đọc trong tiến trình này
        close(pipefd[0]);

        // Chuyển hướng stdout vào pipe write-end
        if (dup2(pipefd[1], STDOUT_FILENO) == -1) {
            perror("dup2 ls");
            exit(EXIT_FAILURE);
        }

        // Đã dup2 xong, có thể đóng pipefd[1]
        close(pipefd[1]);

        // Thực thi "ls -l"
        execlp("ls", "ls", "-l", (char *)NULL);

        // Nếu chạy đến đây là execlp lỗi
        perror("execlp ls");
        exit(EXIT_FAILURE);
    }

    // 3. Tiến trình con 2: thực thi "wc -l"
    pid2 = fork();
    if (pid2 < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid2 == 0) {
        // ----- Child 2 -----
        // Nhận dữ liệu từ đầu đọc của pipe
        // stdin <- pipefd[0]

        // Không dùng đầu ghi trong tiến trình này
        close(pipefd[1]);

        // Chuyển hướng stdin từ pipe read-end
        if (dup2(pipefd[0], STDIN_FILENO) == -1) {
            perror("dup2 wc");
            exit(EXIT_FAILURE);
        }

        // Đã dup2 xong, có thể đóng pipefd[0]
        close(pipefd[0]);

        // Thực thi "wc -l"
        execlp("wc", "wc", "-l", (char *)NULL);

        // Nếu chạy đến đây là execlp lỗi
        perror("execlp wc");
        exit(EXIT_FAILURE);
    }

    // 4. Tiến trình cha: đóng cả hai đầu pipe, chờ con
    close(pipefd[0]);
    close(pipefd[1]);

    // Đợi 2 tiến trình con kết thúc
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    return 0;
}
