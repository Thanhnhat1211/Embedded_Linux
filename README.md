# ⚙️ Linux Process Management

## 📘 Giới thiệu

Trong buổi học hôm nay, tôi đã tìm hiểu về **chương trình (program)** và **tiến trình (process)** — những khái niệm cốt lõi trong hệ điều hành Linux.
Bên cạnh đó, tôi cũng thực hành sử dụng các **system call** như `fork()`, `wait()`, `exit()`, `getpid()`, `getppid()` để quản lý tiến trình, đồng thời tìm hiểu các trạng thái đặc biệt như **Zombie** và **Orphan** process.

---

## 🧩 1. Chương trình (Program) và Tiến trình (Process)

### 🔹 **Chương trình (Program)**

* Là **tệp nhị phân (binary file)** hoặc **mã nguồn** chứa các **câu lệnh** được biên dịch và lưu trữ trong bộ nhớ thứ cấp (như ổ cứng).
* Một chương trình chỉ là **tĩnh** — nó chưa “chạy”.

### 🔹 **Tiến trình (Process)**

* Là **một chương trình đang được thực thi**.
* Khi chương trình được load vào RAM, hệ điều hành tạo ra một tiến trình để quản lý việc thực thi.
* Mỗi tiến trình có không gian bộ nhớ riêng, **PID (Process ID)** duy nhất và **Parent PID (PPID)** chỉ tiến trình cha của nó.

---

## 💻 2. Quan sát tiến trình trên Terminal

Một số lệnh phổ biến để xem thông tin về tiến trình trong Linux:

| Lệnh         | Chức năng                                                            |
| ------------ | -------------------------------------------------------------------- |
| `ps`         | Hiển thị danh sách các tiến trình hiện tại.                          |
| `ps -ef`     | Hiển thị tất cả tiến trình trên hệ thống cùng PID, PPID, trạng thái. |
| `top`        | Theo dõi tiến trình đang chạy theo thời gian thực.                   |
| `htop`       | Phiên bản nâng cao của `top` (nếu được cài đặt).                     |
| `kill <PID>` | Gửi tín hiệu (signal) đến tiến trình để dừng hoặc điều khiển nó.     |

---

## 🌍 3. Tham số môi trường – `argc` và `argv`

Trong hàm `main()` của C:

```c
int main(int argc, char *argv[])
```

* **`argc`**: Số lượng tham số dòng lệnh (bao gồm cả tên chương trình).
* **`argv`**: Mảng các chuỗi ký tự (string array) chứa từng tham số.

Ví dụ:

```bash
./filestat /etc/passwd
```

→ `argc = 2`
→ `argv[0] = "./filestat"`
→ `argv[1] = "/etc/passwd"`

---

## 👶 4. Tạo tiến trình con với `fork()`

* `fork()` được dùng để **tạo một tiến trình con (child process)** từ tiến trình cha.
* Khi gọi `fork()`, hệ thống sẽ **sao chép toàn bộ không gian địa chỉ của tiến trình cha** sang tiến trình con.

### Ví dụ:

```c
int pid = fork();
if(pid == 0)
    printf("This is the child process.\n");
else
    printf("This is the parent process.\n");
```

| Trả về | Ý nghĩa                                          |
| ------ | ------------------------------------------------ |
| 0      | Tiến trình con                                   |
| > 0    | PID của tiến trình con (trả về ở tiến trình cha) |
| < 0    | Lỗi khi tạo tiến trình                           |

---

## 🧭 5. Quản lý tiến trình với các System Call

| System Call | Chức năng                                             |
| ----------- | ----------------------------------------------------- |
| `getpid()`  | Trả về **PID** của tiến trình hiện tại.               |
| `getppid()` | Trả về **PID** của tiến trình cha.                    |
| `wait()`    | Giúp tiến trình cha chờ tiến trình con kết thúc.      |
| `exit()`    | Kết thúc tiến trình hiện tại, trả về giá trị cho cha. |

### Ví dụ:

```c
int pid = fork();
if(pid == 0){
    printf("Child PID: %d, Parent PID: %d\n", getpid(), getppid());
    exit(0);
}
else {
    wait(NULL);
    printf("Child process has finished.\n");
}
```

---

## 🧟‍♂️ 6. Trạng thái đặc biệt: Zombie và Orphan Process

### 🔹 **Zombie Process**

* Xảy ra khi **tiến trình con kết thúc**, nhưng **tiến trình cha chưa gọi `wait()`** để thu thập trạng thái của nó.
* Tiến trình con vẫn tồn tại trong bảng tiến trình với trạng thái `<defunct>`.

### 🔹 **Orphan Process**

* Xuất hiện khi **tiến trình cha kết thúc trước**, trong khi **tiến trình con vẫn đang chạy**.
* Khi đó, tiến trình con sẽ được **`init` (PID 1)** nhận làm cha mới.

### 🔍 **Quan sát trong terminal**

* Sử dụng `ps -ef` để xem:

  ```
  [child] <defunct>   # zombie
  ```
* Quan sát `PPID` của tiến trình orphan thay đổi thành `1` sau khi cha thoát.

---

## 🧪 7. Tổng kết

Qua bài học, tôi đã hiểu:

* Sự khác biệt giữa **chương trình** và **tiến trình**.
* Cách hệ điều hành Linux tạo và quản lý tiến trình.
* Cách sử dụng `fork()`, `wait()`, `exit()` và các system call liên quan.
* Cách quan sát và phân tích các trạng thái đặc biệt như **Zombie** và **Orphan** process.

Đây là kiến thức nền tảng quan trọng để hiểu cách **Linux quản lý đa nhiệm (multitasking)** và **xử lý song song (process control)**.

---

Bạn có muốn mình giúp **xuất file README.md hoàn chỉnh** (Markdown chuẩn sẵn sàng upload GitHub) cho phần này không?
