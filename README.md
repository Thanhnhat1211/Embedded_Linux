# 01_General_Knowledge
Tìm hiểu khái quát về Linux, cách cấu trúc 1 dự án với công cụ hỗ trợ build Makefile và tìm hiểu về các thư viện "Static", "Shared".

---

## 🚀 Giới thiệu
Ở bài này chúng ta sẽ tìm hiểu Linux là gì, các lệnh cơ bản với terminal (thao tác với file, tạo thư mục, tạo file, chuyển đường dẫn, xóa file), cách để sử dụng công cụ hỗ trợ build "Makefile" để tự động hóa 
các tác vụ trong quá trình biên dịch thông qua các Rule, Target nhằm tiết kiệm chi phí thời gian cho 1 dự án, ngoài ra chúng ta cũng sẽ thông qua Makefile để hiểu rõ hơn cấu trúc của 1 dự án thực tế. Cuối cùng là
tìm hiểu các thư viện "Static" và "Shared" hoạt động như thế nào, cách để chúng ta tạo các thư viện đó và biên dịch ra 1 file thực thi hoàn chỉnh.
## 📦 Cài đặt
Đầu tiên chúng ta cần Clone Repository chứa dự án về, sau đó chúng ta sử dụng các file mã nguồn trong thư mục ./src cững như file header trong thư mục ./inc để biên dịch và tạo các file .o vào trong thư mục ./obj.
Sau khi đã có các file thư viện .o ta bắt đầu tạo các thư viện "Static".a và "Shared".so trong thư mục ./lib/static hoặc shared để chuẩn bị cho bước "linking". Cuối cùng ta sử dụng file main.o và linking với các
file thư viện.a hoặc .so để tạo file thực thi
```bash
# Clone repository
git clone https://github.com/username/repository-name.git/tree/Project-name

# Di chuyển vào thư mục
cd project-name

# Cấu trúc của dự án
sudo install tree

#Sử dụng Makefile để tạo ra file thực thi
make all
