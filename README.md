# 📌 LINUX THREAD – PTHREAD

## 🧠 Mục tiêu học tập

* Nắm được **multi-threading** trong Linux và **sự khác nhau với process**.
* Dùng thư viện **POSIX thread (pthread)** để tạo và quản lý thread.
* Hiểu các vấn đề quan trọng:

  * race condition
  * mutual exclusion
  * deadlock
  * shared data

---

## 🔧 Nội dung chính

### 1. Thread vs Process

| Tiêu chí    | Process       | Thread                               |
| ----------- | ------------- | ------------------------------------ |
| Bộ nhớ      | Riêng biệt    | Dùng chung                           |
| Chi phí tạo | Nặng          | Nhẹ                                  |
| Giao tiếp   | IPC           | Dùng chung biến global               |
| Sử dụng     | Đa tiến trình | Xử lý song song trong 1 chương trình |

---

### 2. Thư viện `pthread`

| Mục tiêu       | Hàm quan trọng            |
| -------------- | ------------------------- |
| Tạo thread     | `pthread_create()`        |
| Kết thúc & chờ | `pthread_join()`          |
| Tự kết thúc    | `pthread_exit()`          |
| Mutex khóa     | `pthread_mutex_lock()`    |
| Khởi tạo mutex | `pthread_mutex_init()`    |
| Hủy mutex      | `pthread_mutex_destroy()` |

---

### 3. Các bài thực hành

* Tạo nhiều thread in thông báo.
* Chia task tính toán giữa các thread.
* Sử dụng **mutex** tránh race condition.
* Đếm số từ trong file bằng multi-thread.
* Hiểu **deadlock** và cách tránh.

---

### 4. Vấn đề cần nắm rõ

* Shared resource + mutex
* Thread-safe function
* Thread cancellation
* Synchronization (cond variable / barrier)

---

## 📚 Tài liệu tham khảo

* `man pthread_create`
* `man pthread_mutex_init`
* Linux POSIX Thread Programming
* APUE – Chapter Thread
