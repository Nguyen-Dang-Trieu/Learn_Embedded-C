# Thuật toán LRU
Đọc bài viết này để hiểu rõ cách hoạt động và ứng dụng: https://www.geeksforgeeks.org/system-design/lru-cache-implementation/

## Chi tiết thực hiện
## 1. Array
Ở đây, thực hiện cách đơn giản nhất là dùng array để thể hiện thuật toán. Mặc dù không phải là phương pháp tốt nhất nhưng cho ta cái nhìn toàn diện về cách LRU hoạt động.

Độ phức tạp: O(n) Time and O(n) Space

## 2. Double Linked List + static pool
~~~c
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#define CACHE_CAPACITY 4

typedef struct Node { // Size of Node = 24 bytes (No padding)
  int key;
  int value;
  struct Node *prev, *next;
} Node;

typedef struct { // Size of Cache = 24 bytes (Have padđing: 4)
  Node *head;
  Node *tail;
  int size;
} Cache_Management;

bool pool_used[CACHE_CAPACITY]; // Trạng thái của từng vùng nhớ chứa node

void *initMemoryPool_For_LRUCache(uint8_t cache_capacity) {
  size_t _required_size = sizeof(Cache_Management) + sizeof(Node) * cache_capacity;
  void *_start_memory_pool = (void *)malloc(_required_size);
  if(!_start_memory_pool) {
    printf("\nAlloc memory is failed!\n");
    return NULL;
  }
  memset(_start_memory_pool, 0, _required_size);
  memset(pool_used, 0, sizeof(pool_used));
  
  return _start_memory_pool;
}

void *allocate_memory_From_Pool(void* start_node_memory) 
{
  for(uint8_t i = 0; i < CACHE_CAPACITY; i++) {
    if(pool_used[i] == false) // empty
    {
      pool_used[i] = true;
      return (uint8_t *)start_node_memory + i * sizeof(Node);
    }
  }  
  
  return NULL; // Memory pool has run out of free space
}


void deallocate_memory_To_Pool(void *node_ptr, void *start_node_memory) 
{
  // Important: Luôn phải kiểm tra điền tham số đầu vào
  if (!node_ptr || !start_node_memory) return;
  
  // Tính index của node trong memory pool
  size_t offset = (uint8_t *)node_ptr - (uint8_t *)start_node_memory;
  uint8_t index = offset / sizeof(Node);
  
  if(index >= 0 && index < CACHE_CAPACITY)
    pool_used[index] = false;
}

Node* CreateNode(int key, int value, void *start_node_memory) {
  Node *new = (Node *)allocate_memory_From_Pool(start_node_memory);
  if(!new) 
  {
    printf("\nFailed to create node!\n");
    return NULL;
  }
  
  new->key   = key;
  new->value = value;
  new->prev  = NULL;
  new->next  = NULL;
  
  return new;
}

void moveToHead(Node *node, Cache_Management *LRU) {
  if(!node || node == LRU->head) return;
  
  // Ngắt kết nối
  if (node->prev) node->prev->next = node->next;
  if (node->next) node->next->prev = node->prev;
  if (node == LRU->tail) LRU->tail = node->prev;

  // Chèn vào đầu
  node->next = LRU->head;
  node->prev = NULL;
  LRU->head->prev = node;
  LRU->head = node;

}

int GetCache(int key, void *start_memory_lru) {
  if(!start_memory_lru) return -1;
  
  Cache_Management *LRU = (Cache_Management *)start_memory_lru;
  
  Node *current = LRU->head;
  while(current != NULL) {
    if(key == current->key)
    {
      int value = current->value;
      
      if(current != LRU->head) {
        moveToHead(current, LRU);
      }
      
      return value;
      
    }
    current = current->next;
  }
  
  return -1; // Key not found
}

void PutCache(int key, int value, void *start_memory_lru) {
  // Important: Kiểm tra tham số đầu vào
  if(!start_memory_lru) return;
  
  Cache_Management *LRU = (Cache_Management *)start_memory_lru;
  void *start_node_memory = (uint8_t *)start_memory_lru + sizeof(Cache_Management);
  
  // 1. Kiểm tra xem node đó đã tồn tại chưa (Nếu có rồi thì chỉ cần update)
  Node* current = LRU->head;
  while(current != NULL) {
    if(key == current->key) { // Node tồn tại
      current->value = value;  // Update giá trị của node
      moveToHead(current, LRU); // Move node lên đầu
      return;
    }
    current = current->next;
  }

  // 2. When cache is full, remove the oldest node
  if(LRU->size >= CACHE_CAPACITY) {
    Node *last_node = LRU->tail;
    if(last_node) 
    {
      if(last_node->prev) {
        LRU->tail = last_node->prev;
        LRU->tail->next = NULL;
      } else { // When CACHE_CAPACITY = 1
        LRU->head = LRU->tail = NULL;
      }
    
      deallocate_memory_To_Pool(last_node, start_node_memory);
      LRU->size--;
    }
  }

  // 3. Tạo node và add
  Node *newNode = CreateNode(key, value, start_node_memory);
  if(!newNode) return;

  // 3.1 Add a new node to the begining
  if(LRU->size == 0) { // Cache empty
      LRU->head = LRU->tail = newNode;
  } else {
  
      newNode->next     = LRU->head;
      LRU->head->prev = newNode;
      LRU->head       = newNode;
  }
  LRU->size++;
}


void printCache(void *start_memory_lru) {
  Cache_Management *LRU = (Cache_Management *)start_memory_lru;
    printf("Cache size: %d\n", LRU->size);
    Node *current = LRU->head;
    while (current) {
        printf("[%d:%d]", current->key, current->value);
        if (current->next) printf(" <-> ");
        current = current->next;
    }
    printf("\n");
}

int main()
{
  void *_memoryForLRUCache_ = initMemoryPool_For_LRUCache(CACHE_CAPACITY);
  void *_cache_memory = _memoryForLRUCache_;
  void *start_node_memory = (uint8_t *)_memoryForLRUCache_ + sizeof(Cache_Management);
  
  printf("_memoryForLRUCache_ = %p\n", _memoryForLRUCache_);
  printf("_cache_memory = %p\n", _cache_memory);
  printf("start_node_memory = %p\n", start_node_memory);

  // Chỉ cần gọi PutCache với Key/Value
  PutCache(1, 10, _cache_memory);
  PutCache(2, 20, _cache_memory);
  PutCache(3, 30, _cache_memory);
  PutCache(4, 40, _cache_memory);
  printCache(_cache_memory);

  // Khi thêm key 5, hàm PutCache sẽ tự xóa key 1 rồi mới tạo node cho key 5
  PutCache(3, 100, _cache_memory);
  printCache(_cache_memory);
  
  printf("Gia tri key1: %d\n", GetCache(1, _cache_memory)); 
  printCache(_cache_memory);
  
  printf("Gia tri key3: %d\n", GetCache(3, _cache_memory)); 
  printCache(_cache_memory);

  return 0;
}
~~~

## 3. Hash map + Linked List
