#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void child_handler(int sig) {
    if (sig == SIGUSR1) {
        printf("Child: Received signal from parent\n");
    }
}

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }

    if (pid == 0) {
        // --- CHILD PROCESS ---
        signal(SIGUSR1, child_handler);

        // Child phải chạy liên tục để chờ tín hiệu từ cha
        while (1) {
            pause(); // Chờ tín hiệu
        }
    } 
    else {
        // --- PARENT PROCESS ---
        for (int i = 0; i < 5; i++) {
            sleep(2);
            printf("Parent: Sending SIGUSR1 to child (%d)\n", pid);
            kill(pid, SIGUSR1);   // Gửi tín hiệu
        }

        printf("Parent: Done sending signals. Exiting...\n");
        exit(0);
    }

    return 0;
}
