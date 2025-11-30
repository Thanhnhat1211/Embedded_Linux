# 📌 IPC – PIPE & FIFO

## 🧠 Mục tiêu học tập

* Hiểu cách giao tiếp **liên tiến trình (IPC)** trong Linux thông qua `pipe()` và `FIFO`.
* Phân biệt **pipe ẩn danh** (anonymous pipe) và **pipe có tên** (FIFO – named pipe).
* Tự tạo chương trình **mô phỏng lệnh shell `ls -l | wc -l`** bằng C.

---

## 🔧 Nội dung chính

### 1. Pipe (Ẩn danh – Anonymous Pipe)

* Là cơ chế IPC **chỉ giao tiếp giữa các process có quan hệ cha–con** (nhờ `fork()`).
* Tạo bằng hàm:

```c
int pipe(int fd[2]);  // fd[0] - read end |  fd[1] - write end
```

* Dùng **redirect input/output** với `dup2()` để giả lập pipe trong shell.

💡 Thực hành tiêu biểu:

> Tái tạo lệnh `ls -l | wc -l` bằng C
> → process cha tạo pipe → fork() 2 process con
> → một con chạy `ls -l`, một con chạy `wc -l`
> → dữ liệu tự chảy qua pipe.

---

### 2. FIFO (Named Pipe)

* Là pipe **có tên thật trong filesystem**, giao tiếp được **giữa các process độc lập** (không cần fork).
* Tạo bằng:

```c
mkfifo("mypipe", 0666);
```

* Sau đó dùng như **file đặc biệt**:

```c
open(), read(), write(), close()
```

💡 Dùng như **đường ống liên kết** giữa 2 chương trình chạy riêng biệt:

```
./writer  →  ghi dữ liệu vào pipe
./reader  →  đọc dữ liệu từ pipe
```

---

## 🧪 Ví dụ đã triển khai

| Bài tập | Kiểu giao tiếp                        | Hàm quan trọng                            |                              |
| ------- | ------------------------------------- | ----------------------------------------- | ---------------------------- |
| 1       | Pipe (ẩn danh) – mô phỏng `ls -l      | wc -l`                                    | `pipe()`, `fork()`, `dup2()` |
| 2       | FIFO (có tên) – writer & reader riêng | `mkfifo()`, `open()`, `read()`, `write()` |                              |

---

## 📜 So sánh Pipe & FIFO

| Tính chất                   | Pipe (ẩn danh)                            | FIFO (có tên)                            |
| --------------------------- | ----------------------------------------- | ---------------------------------------- |
| Hiện diện trong filesystem? | ❌ Không                                   | ✔ Có (`ls /tmp/…`)                       |
| Cần quan hệ cha – con?      | ✔ Có                                      | ❌ Không                                  |
| Tạo bởi?                    | `pipe()`                                  | `mkfifo()`                               |
| Dùng khi?                   | Truyền dữ liệu nhanh trong 1 chương trình | Giao tiếp giữa 2 chương trình riêng biệt |
| Song công (2 chiều)?        | ❌ Không                                   | ❌ Không                                  |
| Cơ sở cho shell pipeline    | ✔                                         | ✔                                        |

---

## 📚 API quan trọng

### Pipe:

```c
int pipe(int fd[2]);
dup2(fd[1], STDOUT_FILENO);
dup2(fd[0], STDIN_FILENO);
```

### FIFO:

```c
mkfifo("mypipe", 0666);
open(), read(), write(), close()
```

---

## 🧠 Kết luận

Pipe & FIFO là nền tảng của:

* Cơ chế **pipeline trong shell** (`cmd1 | cmd2 | cmd3…`)
* Tiến trình đa nhiệm trong Linux
* Giao tiếp IPC đơn giản và tốc độ cao
* Kiến trúc **producer–consumer**
* Cơ sở để học tiếp:

  * message queue
  * shared memory
  * socket IPC
