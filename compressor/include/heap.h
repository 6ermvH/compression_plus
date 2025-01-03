#ifndef HEAP_H_INCLUDE
#define HEAP_H_INCLUDE

#include <stddef.h>
#include <stdint.h>

void memswap(void* lhs, void* rhs, size_t size);

typedef struct HEAP {
  void* data;
  size_t sizeElement;
  size_t size;
  size_t capacity;
  int (*compare)(const void*, const void*);
} heap;

void build_h(heap* h, const void* arr, size_t num, size_t size,
                int (*cmp)(const void*, const void*));
void clean_h(heap* h);

void push_h(heap* h, const void* data);
void pop_h(heap* h);

void* top_h(heap* h);

#endif // HEAP_H_INCLUDE
