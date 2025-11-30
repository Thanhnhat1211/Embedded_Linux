// udp_ipv4_server.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 9001
#define BUF_SIZE 1024

int main() {
    int sockfd;
    struct sockaddr_in addr, cliaddr;
    socklen_t cli_len;
    char buf[BUF_SIZE];

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(PORT);

    if (bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("bind");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("UDP IPv4 server listening on port %d...\n", PORT);

    cli_len = sizeof(cliaddr);
    ssize_t n = recvfrom(sockfd, buf, BUF_SIZE - 1, 0,
                         (struct sockaddr *)&cliaddr, &cli_len);
    if (n < 0) {
        perror("recvfrom");
    } else {
        buf[n] = '\0';
        printf("Server received: %s\n", buf);

        const char *reply = "Hello from UDP IPv4 server";
        sendto(sockfd, reply, strlen(reply), 0,
               (struct sockaddr *)&cliaddr, cli_len);
    }

    close(sockfd);
    return 0;
}
