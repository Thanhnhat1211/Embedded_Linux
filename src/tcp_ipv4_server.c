// tcp_ipv4_server.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 9000
#define BUF_SIZE 1024

int main() {
    int listen_fd, conn_fd;
    struct sockaddr_in addr;
    char buf[BUF_SIZE];

    // 1. Tạo socket TCP IPv4
    listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_fd < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // Cho phép reuse địa chỉ (tránh lỗi "Address already in use")
    int opt = 1;
    setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    // 2. Bind đến 0.0.0.0:9000
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;   // 0.0.0.0
    addr.sin_port = htons(PORT);

    if (bind(listen_fd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("bind");
        close(listen_fd);
        exit(EXIT_FAILURE);
    }

    // 3. Listen
    if (listen(listen_fd, 5) < 0) {
        perror("listen");
        close(listen_fd);
        exit(EXIT_FAILURE);
    }

    printf("TCP IPv4 server listening on port %d...\n", PORT);

    // 4. Accept (blocking)
    conn_fd = accept(listen_fd, NULL, NULL);
    if (conn_fd < 0) {
        perror("accept");
        close(listen_fd);
        exit(EXIT_FAILURE);
    }

    // 5. Nhận dữ liệu
    ssize_t n = recv(conn_fd, buf, BUF_SIZE - 1, 0);
    if (n < 0) {
        perror("recv");
    } else {
        buf[n] = '\0';
        printf("Server received: %s\n", buf);

        // 6. Gửi lại phản hồi
        const char *reply = "Hello from TCP IPv4 server";
        send(conn_fd, reply, strlen(reply), 0);
    }

    close(conn_fd);
    close(listen_fd);
    return 0;
}
