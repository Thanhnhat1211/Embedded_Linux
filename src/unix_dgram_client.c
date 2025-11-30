// unix_dgram_client.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SERVER_PATH "/tmp/unix_dgram_server.sock"
#define CLIENT_PATH "/tmp/unix_dgram_client.sock"
#define BUF_SIZE 1024

int main() {
    int sockfd;
    struct sockaddr_un serv_addr, cli_addr;
    char buf[BUF_SIZE];

    sockfd = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // Bind client path để server có chỗ gửi lại
    unlink(CLIENT_PATH);
    memset(&cli_addr, 0, sizeof(cli_addr));
    cli_addr.sun_family = AF_UNIX;
    strncpy(cli_addr.sun_path, CLIENT_PATH, sizeof(cli_addr.sun_path) - 1);

    if (bind(sockfd, (struct sockaddr *)&cli_addr, sizeof(cli_addr)) < 0) {
        perror("bind");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // Địa chỉ server
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sun_family = AF_UNIX;
    strncpy(serv_addr.sun_path, SERVER_PATH, sizeof(serv_addr.sun_path) - 1);

    const char *msg = "Hello from Unix datagram client";
    sendto(sockfd, msg, strlen(msg), 0,
           (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    ssize_t n = recvfrom(sockfd, buf, BUF_SIZE - 1, 0, NULL, NULL);
    if (n >= 0) {
        buf[n] = '\0';
        printf("Client received: %s\n", buf);
    }

    close(sockfd);
    unlink(CLIENT_PATH);
    return 0;
}
