// unix_stream_server.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCK_PATH "/tmp/unix_stream.sock"
#define BUF_SIZE 1024

int main() {
    int listen_fd, conn_fd;
    struct sockaddr_un addr;
    char buf[BUF_SIZE];

    listen_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (listen_fd < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // Xóa file cũ nếu tồn tại
    unlink(SOCK_PATH);

    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SOCK_PATH, sizeof(addr.sun_path) - 1);

    if (bind(listen_fd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("bind");
        close(listen_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(listen_fd, 5) < 0) {
        perror("listen");
        close(listen_fd);
        exit(EXIT_FAILURE);
    }

    printf("Unix stream server listening on %s...\n", SOCK_PATH);

    conn_fd = accept(listen_fd, NULL, NULL);
    if (conn_fd < 0) {
        perror("accept");
        close(listen_fd);
        exit(EXIT_FAILURE);
    }

    ssize_t n = recv(conn_fd, buf, BUF_SIZE - 1, 0);
    if (n >= 0) {
        buf[n] = '\0';
        printf("Server received: %s\n", buf);

        const char *reply = "Hello from Unix stream server";
        send(conn_fd, reply, strlen(reply), 0);
    }

    close(conn_fd);
    close(listen_fd);
    unlink(SOCK_PATH);
    return 0;
}
