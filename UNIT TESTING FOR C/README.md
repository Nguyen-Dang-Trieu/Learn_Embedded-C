## 🌏 Refrence
- https://www.throwtheswitch.org/unity
- https://embetronicx.com/unit-testing-tutorials/
## I. Unity
Để có thể hiểu hơn về Unity thì vui lòng đọc những bài đọc tôi để phần tham khảo phía trên.
### Assertion macro
#### 📌 Nhóm so sánh giá trị nguyên
- TEST_ASSERT_EQUAL(expected, actual)
- TEST_ASSERT_EQUAL_INT(expected, actual)
- TEST_ASSERT_EQUAL_UINT(expected, actual)
- TEST_ASSERT_BITS(mask, expected, actual): Kiểm tra một nhóm bits cụ thể
- TEST_ASSERT_BITS_HIGH(mask, actual)
- TEST_ASSERT_BITS_LOW(mask, actual)
#### 📌 Nhóm kiểm tra bộ nhớ và chuỗi
- TEST_ASSERT_EQUAL_MEMORY(expected, actual, size)
- TEST_ASSERT_EQUAL_STRING(expected, actual)
- TEST_ASSERT_EQUAL_STRING_LEN(expected, actual, len)
- TEST_ASSERT_EQUAL_PTR(p1, p1)

### 1. Các bước để chạy một ví dụ đơn giản
Trước hết ta cần phải vào [github](https://github.com/ThrowTheSwitch/Unity) để lấy 3 file trong thư mục `src/`: `unity_internals.h`, `unity.c`, `unity.h`

Sau đó làm theo hướng dẫn: [Building with Make](https://www.throwtheswitch.org/build/make). Còn nhiều cách khác, bạn có thể tự tìm hiểu

Bước 1: Tạo 5 thư mục 
  - build: chứa các file thực thi và file liên kết.
  - src: toàn bộ file.c
  - inc: chứa file.h
  - test: Định nghĩa các file để tiến hành test
  - unity: chứa `unity_internals.h`, `unity.c`, `unity.h`

Bước 2: Tải [makefile](https://github.com/Nguyen-Dang-Trieu/Learn_Embedded-C/blob/main/UNIT%20TESTING%20FOR%20C/makefile). Có thể sửa makefile để phù hợp với dự án của bản thân.

Bước 3: Tiến hành tạo các file `*.h` và `*.c` cùng với các file test tương ứng.

> [!CAUTION]
> Nếu dùng makefile có sẵn bên trên thì cần phải tuân thủ các quy tắc đặt tên file nếu không sẽ bị lỗi và không compiler được.   
> Thư mục `src/`: Chữ cái đầu tiên tên file **phải viết hoa** - vd: `Calculator.c`   
> Thư mục `inc/`: vd `Calculator.h`   
> Thư mục `test/`: Test + Tên của file.c - vd: `TestCalculator.c`

### 💡 2. Example 
Test các hàm trong thư viện `Calculator.h`

**Cấu trúc thư mục**
~~~
project_root/
├── Makefile
├── src/                     # Code chính (logic của project)
│   ├── Calculator.c
│   └── ...
├── inc/                     # Header file của project
│   ├── Calculator.h
│   └── ...
├── test/                    # Code test (mỗi file test 1 module)
│   ├── TestCalculator.c
│   └── ...
├── unity/                   # Framework Unity (test framework)
│   ├── unity.c
│   ├── unity.h
│   └── unity_internals.h
└── build/                   # Nơi chứa output khi build
    ├── objs/                # Object file (.o)
    ├── depends/             # Dependency file (.d) — optional
    ├── results/             # Kết quả test (.txt)
    └──                      # File .exe / .out nằm ở đây
~~~
Khi làm theo cấu trúc này rồi, dùng `make` để tiến hành test và `make clean` để dọn dẹp các file.

**Đầu ra của ví dụ trên**
~~~
ADMIN@DESKTOP-HSPO3DM MINGW64 ~/Downloads/very-simple-kernel-main/very-simple-kernel-main/unit_test (master)
$ make
mkdir -p build/
mkdir -p build/depends/
mkdir -p build/objs/
mkdir -p build/results/
gcc -c -I. -Iunity/ -Isrc/ -Iinc/ -DTEST test/TestCalculator.c -o build/objs/TestCalculator.o
gcc -c -I. -Iunity/ -Isrc/ -Iinc/ -DTEST src/Calculator.c -o build/objs/Calculator.o
gcc -c -I. -Iunity/ -Isrc/ -Iinc/ -DTEST unity/unity.c -o build/objs/unity.o
gcc -o build/TestCalculator.exe build/objs/TestCalculator.o build/objs/Calculator.o build/objs/unity.o
./build/TestCalculator.exe > build/results/TestCalculator.txt 2>&1
make: [build/results/TestCalculator.txt] Error 1 (ignored)
-----------------------\nIGNORES:\n-----------------------

-----------------------\nFAILURES:\n-----------------------
test/TestCalculator.c:17:test_Addition:FAIL: Expected 6 Was 5 ❌
FAIL
-----------------------\nPASSED:\n-----------------------
test/TestCalculator.c:40:test_Subtraction:PASS
test/TestCalculator.c:41:test_Multiplication:PASS
\nDONE
~~~

Có một test sai ❌ ở đây là do dòng code này trong file `TestCalculator.c`
~~~c
void test_Addition(void) {
    TEST_ASSERT_EQUAL(6, add(2, 3)); ❌
    TEST_ASSERT_EQUAL(0, add(-2, 2));
}
~~~
