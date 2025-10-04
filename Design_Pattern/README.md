# Singleton
Các bài đọc
- https://tinysteps.dev/2024/01/29/creational-singleton-tao-doi-tuong-duy-nhat-cho-chuong-trinh-c/
- https://chiasekinang.com/singleton-pattern-la-gi/
- https://inpyjama.com/post/singleton-pattern/

Triển khai cơ bản của singleton trong c
~~~c
#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int baud_rate;
    bool parity;
    // Add other configurations...
} UartConfig;


typedef struct {
    UartConfig uart_config;
    // Add other members and methods as needed...
} SerialCommunicationManager;

static SerialCommunicationManager communication_manager_instance; // Chưa khởi tạo

// Lấy instance
SerialCommunicationManager* getSerialCommunicationManagerInstance() {
  static bool initialized = false;
  
  if (!initialized) {
    // Initialize UART configuration chỉ một lần duy nhất
    communication_manager_instance.uart_config.baud_rate = 9600;
    communication_manager_instance.uart_config.parity    = false;
    
    printf("[INIT] Serial Communication Manager initialized.\n");
    initialized = true;

  }
    return &communication_manager_instance;
}

// Function to send data via UART
void sendDataViaUart(const char* data) {
    // Lấy instance
    SerialCommunicationManager* communication_manager = getSerialCommunicationManagerInstance();

    // UART send implementation using the configuration
    printf("\n%s\n", data);
    printf("UART Baud Rate: %d\n", communication_manager->uart_config.baud_rate);
    printf("UART Parity: %s\n", communication_manager->uart_config.parity ? "Enabled" : "Disabled");
    // UART implementation details...

    // Additional UART send code...
}

int main() {
    // Get the Serial Communication Manager instance
    SerialCommunicationManager* comm_manager = getSerialCommunicationManagerInstance();

    // Use the Serial Communication Manager to send data via UART
    sendDataViaUart("Parameters before configure UART");

    // Change the Baud Rate universally
    comm_manager->uart_config.baud_rate = 115200;

    // Use the updated Serial Communication Manager to send data via UART
    sendDataViaUart("Parameters after configure UART");

    return 0;
}
~~~
Đầu ra chương trình
~~~
[INIT] Serial Communication Manager initialized.

Parameters before configure UART
UART Baud Rate: 9600
UART Parity: Disabled

Parameters after configure UART
UART Baud Rate: 115200
UART Parity: Disabled
~~~

Tuy nhiên đây chưa phải là tốt nhất bởi vì singleton tồn tại nhiều vấn đề về an toàn thread, nên triển khai safe-thread
