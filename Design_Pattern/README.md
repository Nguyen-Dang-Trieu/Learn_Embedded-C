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

## 💡 Example
~~~c
#include <stdio.h>
#include <stdbool.h>


// Triển khai cơ bản Observer
// Bước 1: Xác định struct của object và Observer
#define MAX_OBSERVERS 10

typedef struct {
  void (*update)(float temperature);
} Observer_t;

typedef struct {
  Observer_t* observers[MAX_OBSERVERS];
  int         observer_count;
  float       temperature;
  
} Subject_t;


// bước 2: Triển khai các hàm của subject
void add_observer(Subject_t* subject, Observer_t* observer) {
  bool exists = false;
  for(int i = 0; i < subject->observer_count; i++) {
    if(subject->observers[i] == observer) {
      exists = true;
      break;
    }
  }
  
  if(!exists && subject->observer_count < MAX_OBSERVERS) {
    subject->observers[subject->observer_count++] = observer;
  }
}

void remove_observer(Subject_t* subject, Observer_t* observer) {
  for(int i = 0; i < subject->observer_count; i++) {
    if(subject->observers[i] == observer) {
      // Thực thi trừ trước rồi mới gán phần cử cuối cùng vào vị trí xóa
      subject->observers[i] = subject->observers[--subject->observer_count];
    }
  }
}

void notify_observers(Subject_t* subject) {
    for (int i = 0; i < subject->observer_count; i++) {
        subject->observers[i]->update(subject->temperature);
    }
}

void set_temperature(Subject_t* subject, float temperature) {
    subject->temperature = temperature;
    notify_observers(subject);
}

// Bước 3: triển khai chức năng của observers
void display_temperature(float temperature) {
    printf("Temperature updated: %.2f\n", temperature);
}

void display_warning(float temperature) {
    if (temperature > 30.0) {
        printf("Warning: High temperature! %.2f\n", temperature);
    }
}


int main()
{
  Subject_t weather_station = { .observer_count = 0, .temperature = 0.0 };

  Observer_t display1 = { .update = display_temperature };
  Observer_t display2 = { .update = display_warning };

  add_observer(&weather_station, &display1);
  add_observer(&weather_station, &display2);

  set_temperature(&weather_station, 25.0);
  set_temperature(&weather_station, 35.0);

  remove_observer(&weather_station, &display1);

  set_temperature(&weather_station, 28.0);


  printf("\nApplication run!\n");
  return 0;
}
Đầu ra chương trình
~~~
Temperature updated: 25.00
Temperature updated: 35.00
Warning: High temperature! 35.00

Application run!
~~~
~~~
