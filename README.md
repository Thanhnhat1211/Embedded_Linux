# 📌 IPC & Socket Programming – Overview

## 🧠 Mục tiêu học tập

* Hiểu **khái niệm giao tiếp liên tiến trình (IPC)** trong hệ thống Unix/Linux.
* Nắm được nền tảng của **socket programming** – cơ chế giao tiếp qua **network hoặc nội bộ hệ thống**.
* Cài đặt được **các cặp client-server đơn giản** bằng C/POSIX.

---

## 🔧 Nội dung chính

### 1. Tổng quan IPC (Inter-Process Communication)

* Lý do cần IPC
* Các cơ chế phổ biến:

  * Pipe / FIFO
  * Shared Memory
  * Message Queue
  * **Socket (quan trọng nhất)**

---

### 2. Socket Programming

Socket là cơ chế IPC **đồng thời dùng được cho mạng máy tính**.

Hai nhóm chính:

| Loại Socket | Mục đích                        | Giao thức         | Giải thích ngắn                      |
| ----------- | ------------------------------- | ----------------- | ------------------------------------ |
| IPv4 Socket | Giao tiếp qua mạng LAN/Internet | TCP / UDP         | Dùng IP + Port để kết nối            |
| Unix Socket | Giao tiếp nội bộ trong cùng máy | Stream / Datagram | Nhanh hơn vì không qua network stack |

---

### 3. Các bài đã triển khai

| Bài tập | Loại Socket          | Giao thức   |
| ------- | -------------------- | ----------- |
| 1       | IPv4 Stream Socket   | TCP         |
| 2       | IPv4 Datagram Socket | UDP         |
| 3       | Unix Stream Socket   | SOCK_STREAM |
| 4       | Unix Datagram Socket | SOCK_DGRAM  |

Mỗi bài gồm **cặp chương trình `client` – `server`**, truyền một chuỗi dữ liệu đơn giản.

---

## 🧪 Cách chạy ví dụ (minh họa)

```bash
# Biên dịch
gcc tcp_ipv4_server.c -o server
gcc tcp_ipv4_client.c -o client

# Chạy
./server        # chạy trước
./client        # chạy sau
```

---

## 📌 Ghi chú quan trọng

* TCP cần `connect()` → đảm bảo **reliable & connection-oriented**
* UDP dùng `sendto()` / `recvfrom()` → **nhanh nhưng không đảm bảo**
* Unix socket chỉ chạy **trong cùng một máy**, rất hữu ích cho IPC
* `accept()` là **blocking call** → cần dùng đa luồng hoặc `select()` nếu muốn xử lý nhiều client

---

## 📚 Tài liệu tham khảo

* `man 2 socket`, `man 2 bind`, `man 2 connect`, `man 2 recv`
* Beej’s Guide to Network Programming
* Linux Programmer’s Manual

---

## ✔ Kết luận

Socket là nền tảng của:

* Web server (HTTP)
* SSH, FTP, DNS
* Database client-server
* Load balancer, Proxy, Cloud service
* Giao tiếp IPC hiệu quả giữa các process

⚡ **Nắm vững socket = hiểu cách Internet hoạt động + hiểu hệ thống bên trong.**
