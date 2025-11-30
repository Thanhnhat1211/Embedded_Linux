// unix_dgram_server.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SERVER_PATH "/tmp/unix_dgram_server.sock"
#define BUF_SIZE 1024

int main() {
    int sockfd;
    struct sockaddr_un serv_addr, cli_addr;
    socklen_t cli_len;
    char buf[BUF_SIZE];

    sockfd = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    unlink(SERVER_PATH);

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sun_family = AF_UNIX;
    strncpy(serv_addr.sun_path, SERVER_PATH, sizeof(serv_addr.sun_path) - 1);

    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("bind");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("Unix datagram server listening on %s...\n", SERVER_PATH);

    cli_len = sizeof(cli_addr);
    ssize_t n = recvfrom(sockfd, buf, BUF_SIZE - 1, 0,
                         (struct sockaddr *)&cli_addr, &cli_len);
    if (n >= 0) {
        buf[n] = '\0';
        printf("Server received: %s\n", buf);

        const char *reply = "Hello from Unix datagram server";
        sendto(sockfd, reply, strlen(reply), 0,
               (struct sockaddr *)&cli_addr, cli_len);
    }

    close(sockfd);
    unlink(SERVER_PATH);
    return 0;
}
