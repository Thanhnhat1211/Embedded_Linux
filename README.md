# 📌 IPC – SIGNAL

## 🧠 Mục tiêu học tập

* Hiểu cơ chế **Signal trong Linux** như một hình thức **giao tiếp bất đồng bộ** giữa các tiến trình.
* Biết cách **bắt – xử lý – tạo tín hiệu** (`signal handling` & `signal sending`).
* Nắm được **tín hiệu mặc định của hệ thống** (SIGINT, SIGTERM, SIGKILL, SIGCHLD…).

---

## 🔧 Nội dung chính

### 1. Signal là gì?

* Là **thông điệp hệ thống gửi đến process** để báo hiệu một sự kiện (interrupt, kill, stop,...).
* Mang tính **asynchronous IPC** — quá trình nhận không biết trước khi nào tín hiệu đến.

---

### 2. Các tín hiệu quan trọng

| Signal  | Ý nghĩa                      |
| ------- | ---------------------------- |
| SIGINT  | Ctrl + C                     |
| SIGKILL | Kill ngay, không xử lý được  |
| SIGTERM | Yêu cầu kết thúc “đúng cách” |
| SIGSTOP | Tạm dừng tiến trình          |
| SIGCHLD | Con chết → thông báo cho cha |
| SIGALRM | Hẹn giờ (timer)              |
| SIGHUP  | Mất kết nối terminal         |

---

### 3. Các thao tác chính

| Công việc                    | Hàm dùng                   |
| ---------------------------- | -------------------------- |
| Bắt tín hiệu                 | `signal()` / `sigaction()` |
| Gửi tín hiệu từ chương trình | `kill()`                   |
| Gửi tín hiệu hệ thống        | `raise()`                  |
| Tạo timer gọi signal         | `alarm()`                  |

---

### 4. Mục tiêu thực hành

* Cài đặt chương trình **nhận Ctrl+C nhưng không chết**.
* Tạo handler custom cho SIGTERM.
* Gửi tín hiệu giữa **2 process** bằng `kill(pid, signal)`.
* Sử dụng `alarm()` để tạo **timeout**.

---

## 📚 Tài liệu tham khảo

* `man 7 signal`, `man 2 kill`, `man 2 sigaction`
* Advanced Programming in the UNIX Environment (APUE)
* TLDP: Introduction to Signals
