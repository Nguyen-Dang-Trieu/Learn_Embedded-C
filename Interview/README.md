## ❓ Câu hỏi 1: Con trỏ và mảng
Giải thích sự khác nhau giữa con trỏ và mảng trong C. 
Trong trường hợp nào chúng có thể được sử dụng thay thế nhau, và khi 
nào thì không?

### 🔍 Lời đáp
Con trỏ là biến lưu địa chỉ, còn mảng là vùng nhớ liên tiếp.

#### Về khả năng thay thế nhau:
Con trỏ và mảng có thể truy cập dữ liệu giống nhau bằng cú pháp `ptr[i]`, nhưng chúng không hoàn toàn thay thế nhau về mặt ngữ nghĩa và quản lý bộ nhớ.   
**Ví dụ:**
~~~c
int arr[5];       // Mảng có kích thước cố định, bộ nhớ cấp phát tại compile-time
int *ptr = arr;   // Con trỏ trỏ tới mảng
~~~
Nhưng:
~~~c
int *ptr = malloc(5 * sizeof(int)); // Con trỏ trỏ tới vùng nhớ động
~~~
#### Kích thước
- Mảng có kích thước cố định, nhưng con trỏ có thể trỏ tới vùng nhớ có kích thước thay đổi (thường dùng với `malloc`, `calloc`).

Khi truyền mảng vào hàm, nó suy biến thành con trỏ, và ta không thể biết kích thước mảng trong hàm nếu không truyền thêm thông tin.

#### sizeof:
- `sizeof(arr)` sẽ trả về tổng kích thước mảng.
- `sizeof(ptr)` chỉ trả về kích thước con trỏ (thường là 4 hoặc 8 bytes tùy hệ thống).


### 📌 Câu hỏi follow-up (đào sâu):

Nếu bạn có đoạn code `int arr[10]; int *ptr = arr;`, bạn có thể dùng `ptr++` để duyệt mảng. Vậy điều gì xảy ra nếu bạn viết `arr++`?

Gây ra lỗi biên dịch, vì arr là tên của mảng, biểu diễn địa chỉ của phần tử đầu tiên, nhưng không phải là một biến con trỏ có thể thay đổi giá trị.
Trong C, tên mảng hoạt động giống như một hằng con trỏ (constant pointer) trỏ đến phần tử đầu tiên, nên không thể thực hiện phép arr++.

`int *const ptr`; <- Hằng số con trỏ, địa chỉ con trỏ cố định


## ❓Câu hỏi 2: Volatile
Từ khóa `volatile` dùng để làm gì trong C? Cho ví dụ cụ thể trong hệ thống nhúng mà nếu thiếu `volatile` sẽ gây lỗi.

### 🔍 Lời đáp
Một biến dùng `volatile` sẽ thông báo cho compiler là không tối ưu hóa biến đó, và giá trị của nó có thể thay đổi do phần cứng.

Cụ thể hơn về “tối ưu hóa”:
- Compiler có thể lưu giá trị biến vào thanh ghi CPU để tăng tốc độ truy cập.
- Nếu biến đó thay đổi bởi ngoại cảnh (interrupt, DMA, phần cứng), thì giá trị trong thanh ghi CPU sẽ không còn đúng.
- `volatile` đảm bảo mỗi lần truy cập đều đọc trực tiếp từ địa chỉ bộ nhớ, không dùng bản sao tạm.

**Ví dụ:**
~~~c
volatile uint8_t status_reg;

while (status_reg != READY) {
    // chờ phần cứng cập nhật status_reg
}
~~~
Nếu thiếu `volatile`, compiler có thể tối ưu bằng cách đọc `status_reg` một lần rồi dùng lại trong vòng lặp — dẫn đến vòng lặp không bao giờ kết thúc.

#### Tình huống phổ biến cần dùng volatile:
- Biến được cập nhật trong ISR (Interrupt Service Routine)
- Biến ánh xạ tới thanh ghi phần cứng
- Biến dùng trong **multi-threading** hoặc **RTOS task** (dù cần thêm atomic hoặc mutex để đảm bảo an toàn)

### 📌 Câu hỏi follow-up (đào sâu):
Nếu ta có biến `volatile int flag`; được cập nhật trong `ISR`, bạn có cần thêm `volatile` khi dùng trong hàm `main()` không? Tại sao?
~~~c
volatile int flag = 0;

void ISR_Handler() {
    flag = 1; // ISR cập nhật biến
}

int main() {
    while (!flag) {
        // chờ ISR cập nhật flag
    }
    // tiếp tục xử lý
}
~~~
Trong ví dụ này, biến `flag` được dùng ở cả ISR và main(), nên bạn phải khai báo `volatile` để đảm bảo:
- Compiler không tối ưu hóa vòng lặp trong `main()` bằng cách **lưu flag vào thanh ghi**.
- Mỗi lần kiểm tra flag, chương trình sẽ đọc trực tiếp từ bộ nhớ, nơi ISR có thể đã thay đổi giá trị.

👉 **Kết luận**
Có, cần phải dùng `volatile` khi truy cập biến đó ở main() — không phải vì main() thay đổi nó, mà vì giá trị có thể thay đổi ngoài tầm kiểm soát của main(), cụ thể là từ ISR.
