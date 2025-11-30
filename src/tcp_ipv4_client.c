// tcp_ipv4_client.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"
#define PORT 9000
#define BUF_SIZE 1024

int main() {
    int sockfd;
    struct sockaddr_in serv_addr;
    char buf[BUF_SIZE];

    // 1. Tạo socket TCP
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // 2. Thiết lập địa chỉ server
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, SERVER_IP, &serv_addr.sin_addr);

    // 3. Kết nối
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("connect");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // 4. Gửi dữ liệu
    const char *msg = "Hello from TCP IPv4 client";
    send(sockfd, msg, strlen(msg), 0);

    // 5. Nhận phản hồi
    ssize_t n = recv(sockfd, buf, BUF_SIZE - 1, 0);
    if (n >= 0) {
        buf[n] = '\0';
        printf("Client received: %s\n", buf);
    }

    close(sockfd);
    return 0;
}
