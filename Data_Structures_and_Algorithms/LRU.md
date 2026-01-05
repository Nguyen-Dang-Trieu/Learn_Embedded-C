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

// Cache 
typedef struct {
  int  (*get)  (void *ctx, int key, int *value);
  void (*put)  (void *ctx, int key, int value);
  void (*print)(void *ctx); 
} Cache_ops_t;


typedef struct {
  Cache_ops_t *ops;  // Các phương thức của cache
  void        *ctx;  // Trỏ đến tối tượng cache 
} Cache_t;

void Cache_init(Cache_t *c, void *ctx, Cache_ops_t* ops) 
{
  c->ops = ops;
  c->ctx = ctx;
}

void Cache_Put(Cache_t *c, int key, int value) 
{
  c->ops->put(c->ctx, key, value);
}

int Cache_Get(Cache_t *c, int key, int *value) 
{
 return c->ops->get(c->ctx, key, value); 
}

void Cache_Print(Cache_t *c)
{
    c->ops->print(c->ctx);
}


// LRU
#define CACHE_CAPACITY 4

typedef struct LRU LRU_t;
/* ==== LRU API PROTOTYPES ==== */
void LRU_Init(LRU_t *lru);
int  LRU_Get (LRU_t *lru, int key);
void LRU_Put (LRU_t *lru, int key, int value);
void LRU_Print(LRU_t *lru);


// LRU Adapter -> giải thích tại sao phải gọi là adapter?
static int LRU_Get_adapter(void *ctx, int key, int *value)
{
  LRU_t *lru = (LRU_t *)ctx;
  int v = LRU_Get(lru, key);   
  if (v < 0)
    return -1; // Key không tồn tại           

  *value = v;
  return 1;                    
}

static void LRU_Put_adapter(void *ctx, int key, int value)
{
  LRU_t *lru = (LRU_t *)ctx;
  LRU_Put(lru, key, value);   
}

static void LRU_Print_adapter(void *ctx)
{
  LRU_t *lru = (LRU_t *)ctx;
  LRU_Print(lru);
}


Cache_ops_t LRU_ops = {
  .put   = LRU_Put_adapter,
  .get   = LRU_Get_adapter,
  .print = LRU_Print_adapter
};

typedef struct LRU_Node { // Size of Node = 24 bytes (No padding)
  int key;
  int value;
  struct LRU_Node *prev, *next;
} LRU_Node_t;

typedef struct { // Size of Cache = 24 bytes (Have padđing: 4)
  LRU_Node_t *head;
  LRU_Node_t *tail;
  int         size;
} LRU_List_t;

struct LRU {
  LRU_List_t list;
  bool       used_pool[CACHE_CAPACITY]; // Đánh dấu các vùng nhớ đã được dùng
  void       *node_pool;           // Địa chỉ bắt đầu vùng memory pool cho node
};

void LRU_Init(LRU_t *lru) {
  size_t required_size = sizeof(LRU_Node_t) * CACHE_CAPACITY;
  void   *start_pool   = (void *)malloc(required_size);
  
  if(!start_pool) {
    printf("\nAlloc memory is failed!\n");
    return;
  }
  memset(start_pool, 0, required_size);
  memset(lru->used_pool, 0, sizeof(lru->used_pool));
  lru->node_pool = start_pool;
}

/**
 * @brief Cấp phát vùng nhớ từ pool cho node
 * @param void None
 * @retval Địa chỉ bắt đầu vùng nhớ của node
 */
static void *allocate_node_From_Pool(LRU_t *lru) {
  void *start_memory = lru->node_pool; // Địa chỉ bắt đầu memory pool dành cho node
  
  for(uint8_t i = 0; i < CACHE_CAPACITY; i++) {
    if(lru->used_pool[i] == false) { // empty 
      lru->used_pool[i] = true;
      return (uint8_t *)start_memory + i * sizeof(LRU_Node_t);
    }
  }  
  
  return NULL; // Memory pool has run out of free space
}

/**
 * @brief Giải phóng vùng nhớ của một node trong memory pool
 * @param node_ptr Trỏ tới node muốn giải phóng
 */
static void deallocate_node_To_Pool(LRU_t *lru, void *node_ptr) 
{
  void *start_memory = lru->node_pool; // Địa chỉ bắt đầu memory pool dành cho node
  
  // Important: Luôn phải kiểm tra điền tham số đầu vào
  if (!node_ptr || !start_memory) return;
  
  // Tính index của node trong memory pool
  size_t offset = (uint8_t *)node_ptr - (uint8_t *)start_memory;
  uint8_t index = offset / sizeof(LRU_Node_t);
  
  if(index >= 0 && index < CACHE_CAPACITY)
    lru->used_pool[index] = false;
}

static LRU_Node_t* CreateNode(LRU_t *lru, int key, int value) 
{
  void *start_memory = lru->node_pool; // Địa chỉ bắt đầu memory pool dành cho node
  
  LRU_Node_t *new = (LRU_Node_t *)allocate_node_From_Pool(lru);
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

/**
 * @brief Di chuyển node vừa thao tác lên vị trí head của list
 * @param node Node muốn thao tác
 * @param list_node Danh sách node hiện tại của lru
 */
static void moveToHead(LRU_Node_t *node, LRU_List_t *list_node) 
{
  if(!node || node == list_node->head) return;
  
  // Ngắt kết nối
  if (node->prev) node->prev->next = node->next;
  if (node->next) node->next->prev = node->prev;
  if (node == list_node->tail) list_node->tail = node->prev;

  // Chèn vào đầu
  node->next            = list_node->head;
  node->prev            = NULL;
  if(list_node->head) list_node->head->prev = node;
  list_node->head       = node;

}

int LRU_Get(LRU_t *lru, int key) 
{
  LRU_List_t *list_node = &lru->list;
  
  LRU_Node_t *current = list_node->head;
  while(current != NULL) {
    if(key == current->key)
    {
      int value = current->value;
      
      if(current != list_node->head) {
        moveToHead(current, list_node);
      }
      
      return value;
      
    }
    current = current->next;
  }
  
  return -1; // Key not found
}

void LRU_Put(LRU_t *lru, int key, int value) 
{
  LRU_List_t *list_node = &lru->list;
  void *start_memory = lru->node_pool; // Địa chỉ bắt đầu memory pool dành cho node
  
  // 1. Kiểm tra xem node đó đã tồn tại chưa (Nếu có rồi thì chỉ cần update)
  LRU_Node_t* current = list_node->head;
  while(current != NULL) {
    if(key == current->key) { // Node tồn tại
      current->value = value;  // Update giá trị của node
      moveToHead(current, list_node); // Move node lên đầu
      return;
    }
    current = current->next;
  }

  // 2. When cache is full, remove the oldest node
  if(list_node->size >= CACHE_CAPACITY) {
    LRU_Node_t *last_node = list_node->tail;
    if(last_node) 
    {
      if(last_node->prev) {
        list_node->tail = last_node->prev;
        list_node->tail->next = NULL;
      } else { // When CACHE_CAPACITY = 1
        list_node->head = list_node->tail = NULL;
      }
    
      deallocate_node_To_Pool(lru, last_node);
      list_node->size--;
    }
  }

  // 3. Tạo node và add
  LRU_Node_t *newNode = CreateNode(lru, key, value);
  if(!newNode) return;

  // 3.1 Add a new node to the begining
  if(list_node->size == 0) { // Cache empty
      list_node->head = list_node->tail = newNode;
  } else {
  
      newNode->next         = list_node->head;
      list_node->head->prev = newNode;
      list_node->head       = newNode;
  }
  list_node->size++;
}


void LRU_Print(LRU_t *lru) 
{
  LRU_List_t *list_node = &lru->list;  // Danh sách node của lru
  printf("Cache size: %d\n", list_node->size);
  LRU_Node_t *current = list_node->head;

  while (current) {
        printf("[%d:%d]", current->key, current->value);
        if (current->next) printf(" <-> ");
        current = current->next;
  }
  printf("\n");
}

int main()
{
  Cache_t cacheSystem;
  LRU_t   lruCache;
  LRU_Init(&lruCache);
  Cache_init(&cacheSystem, &lruCache, &LRU_ops);

  Cache_Put(&cacheSystem, 1, 100);
  Cache_Put(&cacheSystem, 2, 200);
  Cache_Put(&cacheSystem, 3, 300);
  Cache_Put(&cacheSystem, 4, 400);
  Cache_Print(&cacheSystem);
  
  Cache_Put(&cacheSystem, 1, 500);
  Cache_Print(&cacheSystem);

  return 0;
}
~~~

## 3. Hash map + Linked List
