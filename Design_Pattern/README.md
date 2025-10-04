# Singleton
Các bài đọc
- https://tinysteps.dev/2024/01/29/creational-singleton-tao-doi-tuong-duy-nhat-cho-chuong-trinh-c/
- https://chiasekinang.com/singleton-pattern-la-gi/
- https://inpyjama.com/post/singleton-pattern/

## 💡 Example 
Triển khai một singleton cơ bản để quản lí thông số của UART trong Embedded Systems
~~~c
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

typedef enum {
    PARITY_NONE,
    PARITY_EVEN,
    PARITY_ODD
} ParityType;

typedef struct {
    uint16_t   baud_rate;
    uint8_t    data_bits;
    uint8_t    stop_bits;
    ParityType parity;
} UartConfig;

typedef struct {
    UartConfig uart_config;
    bool       isInitialized;
} SerialCommunicationManager;

static SerialCommunicationManager communication_manager_instance;

// Hàm khởi tạo cấu hình UART
void initializeUartConfig(UartConfig* config, int baud_rate, int data_bits, int stop_bits, ParityType parity) {
    config->baud_rate = baud_rate;
    config->data_bits = data_bits;
    config->stop_bits = stop_bits;
    config->parity    = parity;
}

// Lấy instance Singleton
SerialCommunicationManager* getSerialCommunicationManagerInstance() {
    if (!communication_manager_instance.isInitialized) {
        initializeUartConfig(&communication_manager_instance.uart_config, 9600, 8, 1, PARITY_NONE);
        communication_manager_instance.isInitialized = true;
        printf("[INIT] Serial Communication Manager initialized.\n");
    }
    return &communication_manager_instance;
}

// Hàm gửi dữ liệu UART
void sendDataViaUart(const char* data) {
    SerialCommunicationManager* manager = getSerialCommunicationManagerInstance();
    UartConfig* config = &manager->uart_config;

    printf("\nSending: %s\n", data);
    printf("UART Config:\n");
    printf("  Baud Rate: %d\n", config->baud_rate);
    printf("  Data Bits: %d\n", config->data_bits);
    printf("  Stop Bits: %d\n", config->stop_bits);
    printf("  Parity: %s\n", 
        config->parity == PARITY_NONE ? "None" :
        config->parity == PARITY_EVEN ? "Even" : "Odd");

    // Thêm logic gửi thực tế ở đây...
}

int main() {
    SerialCommunicationManager* manager = getSerialCommunicationManagerInstance();

    sendDataViaUart("Initial UART configuration");

    // Cập nhật cấu hình UART
    initializeUartConfig(&manager->uart_config, 115200, 8, 1, PARITY_EVEN);

    sendDataViaUart("Updated UART configuration");

    return 0;
}
~~~
Đầu ra chương trình
~~~
[INIT] Serial Communication Manager initialized.

Sending: Initial UART configuration
UART Config:
  Baud Rate: 9600
  Data Bits: 8
  Stop Bits: 1
  Parity: None

Sending: Updated UART configuration
UART Config:
  Baud Rate: 49664
  Data Bits: 8
  Stop Bits: 1
  Parity: Even
~~~

Tuy nhiên đây chưa phải là tốt nhất bởi vì singleton tồn tại nhiều vấn đề về an toàn thread, nên triển khai safe-thread

# Observer
https://peerdh.com/blogs/programming-insights/implementing-the-observer-pattern-in-c-with-function-pointers
