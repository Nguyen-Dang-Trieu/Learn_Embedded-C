## Refrence
- https://www.throwtheswitch.org/unity
- https://embetronicx.com/unit-testing-tutorials/
## Unity
Trước hết ta cần phải vào [github](https://github.com/ThrowTheSwitch/Unity) để lấy 3 file trong thư mục `src/`: `unity_internals.h`, `unity.c`, `unity.h`

Sau đó làm theo hướng dẫn: [Building with Make](https://www.throwtheswitch.org/build/make). Còn nhiều cách khác, bạn có thể tự tìm hiểu

### Các bước để test một ví dụ đơn giản
Bước 1: Tạo 5 thư mục 
  - build: chứa các file thực thi và file liên kết.
  - src: toàn bộ file.c
  - inc: chứa file.h
  - test: Định nghĩa các file để tiến hành test
  - unity: chứa `unity_internals.h`, `unity.c`, `unity.h`

Bước 2: Tải [makefile]()
