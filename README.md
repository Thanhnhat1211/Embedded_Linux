# 🧩 Linux File System – System Calls, Permissions, and File Control

## 📘 Giới thiệu

Trong chủ đề **Linux File System**, tôi được học về cách hệ điều hành Linux quản lý tệp tin (file) và thư mục (directory) thông qua các **system call** ở tầng nhân (kernel level).
Các nội dung chính bao gồm:

* Thay đổi quyền truy cập (permission) của file/thư mục.
* Các system call phổ biến dùng trong quản lý file.
* Cơ chế **file locking** và **file control**.
* Thực hành viết chương trình đọc thông tin chi tiết của một file bằng **`lstat()`**.

---

## 🔐 Thay đổi quyền truy cập (File Permissions)

Trong Linux, mỗi file hoặc thư mục có 3 loại quyền truy cập cơ bản:

* **Read (r)** – quyền đọc nội dung file.
* **Write (w)** – quyền ghi hoặc chỉnh sửa nội dung file.
* **Execute (x)** – quyền thực thi file (nếu là chương trình hoặc script).

Quyền này được gán cho ba nhóm người dùng:

| Ký hiệu | Nhóm người dùng   | Ví dụ quyền |
| ------- | ----------------- | ----------- |
| `u`     | User (chủ sở hữu) | rwx------   |
| `g`     | Group             | ---r-x---   |
| `o`     | Others            | ------r-x   |

### Các lệnh thay đổi quyền:

```bash
chmod 755 file_name       # rwxr-xr-x
chmod u+x file_name       # thêm quyền execute cho user
chown user:group file_name  # thay đổi quyền sở hữu
```

---

## ⚙️ System Calls liên quan đến File System

Một số system call cơ bản để thao tác với file trong Linux:

| System Call           | Mô tả                                                                          |
| --------------------- | ------------------------------------------------------------------------------ |
| `open()`              | Mở hoặc tạo một file.                                                          |
| `read()`              | Đọc dữ liệu từ file descriptor.                                                |
| `write()`             | Ghi dữ liệu vào file descriptor.                                               |
| `close()`             | Đóng file đang mở.                                                             |
| `lseek()`             | Di chuyển con trỏ đọc/ghi trong file.                                          |
| `stat()` / `lstat()`  | Lấy thông tin chi tiết về file (kích thước, quyền, thời gian chỉnh sửa, v.v.). |
| `unlink()`            | Xóa file khỏi hệ thống.                                                        |
| `chmod()` / `chown()` | Thay đổi quyền hoặc chủ sở hữu của file.                                       |

---

## 🔒 File Locking & File Control

Khi nhiều tiến trình truy cập cùng một file, có thể xảy ra xung đột dữ liệu.
Linux hỗ trợ **file locking** để đảm bảo đồng bộ truy cập:

### 1️⃣ **Advisory Locking** (khóa mang tính tự nguyện)

Sử dụng `fcntl()` hoặc `flock()` để đặt hoặc gỡ khóa:

```c
fcntl(fd, F_SETLK, &lock);  // Đặt khóa
fcntl(fd, F_UNLCK, &lock);  // Gỡ khóa
```

### 2️⃣ **Mandatory Locking** (khóa bắt buộc)

Khi file được gán quyền đặc biệt, hệ thống sẽ **bắt buộc** tuân thủ cơ chế khóa khi truy cập, giúp tránh ghi đè dữ liệu.

---

## 💻 Bài tập thực hành

### 🎯 **Đề bài:**

Viết chương trình đọc thông tin của một file hoặc thư mục, bao gồm:

* Đường dẫn file.
* Loại file (regular, directory, symbolic link, etc.).
* Kích thước file.
* Thời gian chỉnh sửa lần cuối.

### 📄 **Mã nguồn:**

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>

int main(int argc, char *argv[]){
    if(argc != 2){
        printf("Usage: %s <file_path>\n", argv[0]);
        return 1;
    }

    struct stat st;
    if(lstat(argv[1], &st) == -1){
        perror("lstat");
        return 1;
    }

    char file_type[30];
    if(S_ISREG(st.st_mode))
        strcpy(file_type, "Regular File");
    else if(S_ISDIR(st.st_mode))
        strcpy(file_type, "Directory");
    else if(S_ISLNK(st.st_mode))
        strcpy(file_type, "Symbolic Link");
    else
        strcpy(file_type, "Other");

    char last_modified[100];
    struct tm *tm_info = localtime(&st.st_mtime);
    strftime(last_modified, sizeof(last_modified), "%d-%m-%Y %H:%M:%S", tm_info);

    printf("File path      : %s\n", argv[1]);
    printf("File type      : %s\n", file_type);
    printf("Size (bytes)   : %ld\n", st.st_size);
    printf("Last modified  : %s\n", last_modified);

    return 0;
}
```

**Kết quả mẫu:**

```
File path      : /etc/passwd
File type      : Regular File
Size (bytes)   : 2733
Last modified  : 10-11-2025 08:21:13
```

---

## 📚 **Tổng kết**

Sau bài học này, tôi đã hiểu rõ:

* Cách thay đổi quyền và quyền sở hữu file trong Linux.
* Cách sử dụng **system calls** để truy cập và thao tác với file.
* Cách kiểm soát truy cập đồng thời qua **file locking**.
* Cách lấy thông tin chi tiết của file bằng **`lstat()`** và **`struct stat`**.

👉 Đây là nền tảng quan trọng để phát triển các chương trình cấp hệ thống (system-level programming) và hiểu cách nhân Linux quản lý tài nguyên.

---

Nếu bạn muốn, mình có thể **xuất file này thành `README.md` hoàn chỉnh** (đúng định dạng Markdown để upload lên GitHub). Bạn có muốn mình tạo file đó luôn không?
