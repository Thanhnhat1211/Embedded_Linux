// udp_ipv4_client.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"
#define PORT 9001
#define BUF_SIZE 1024

int main() {
    int sockfd;
    struct sockaddr_in serv_addr;
    socklen_t serv_len;
    char buf[BUF_SIZE];

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, SERVER_IP, &serv_addr.sin_addr);
    serv_len = sizeof(serv_addr);

    const char *msg = "Hello from UDP IPv4 client";
    sendto(sockfd, msg, strlen(msg), 0,
           (struct sockaddr *)&serv_addr, serv_len);

    ssize_t n = recvfrom(sockfd, buf, BUF_SIZE - 1, 0,
                         (struct sockaddr *)&serv_addr, &serv_len);
    if (n >= 0) {
        buf[n] = '\0';
        printf("Client received: %s\n", buf);
    }

    close(sockfd);
    return 0;
}
