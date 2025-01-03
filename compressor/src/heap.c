#include "heap.h"

#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

void memswap(void* lhs, void* rhs, size_t size) {
  void* tmp = malloc(size);
  memcpy(tmp, lhs, size);
  memcpy(lhs, rhs, size);
  memcpy(rhs, tmp, size);
  free(tmp);
}

static size_t update_h(heap* h, size_t ind) {
  if (ind > 0) {
    size_t p = (ind - 1) / 2;
    if (h->compare(h->data + ind * h->sizeElement, h->data + p * h->sizeElement) < 0) {
      memswap(h->data + ind * h->sizeElement, h->data + p * h->sizeElement, h->sizeElement);
    }
  }
  size_t result = h->size * h->sizeElement;
  size_t l = ind * 2 + 1,
         r = ind * 2 + 2;
  ind *= h->sizeElement;
  if (h->size <= l) return result / h->sizeElement;
  l *= h->sizeElement;
  if (h->compare(h->data + l, h->data + ind) < 0) {
    memswap(h->data + l, h->data + ind, h->sizeElement);
    result = l;
  }
  if (h->size <= r) return result / h->sizeElement;
  r *= h->sizeElement;
  if (h->compare(h->data + r, h->data + ind) < 0) {
    memswap(h->data + r, h->data + ind, h->sizeElement);
    if (result != l) {
      result = r;
    }
  }

  return result / h->sizeElement;
}

static void update_capacity_h(heap* h) {
  h->capacity *= 2;
  void* newData = malloc(h->capacity * h->sizeElement);
  memcpy(newData, h->data, h->size * h->sizeElement);
  free(h->data);
  h->data = newData;
}

void init_h(heap* h, size_t size, int (*cmp)(const void*, const void*)) {
  h->sizeElement = size;
  h->size = 0;
  h->capacity = 2;
  h->compare = cmp;
}

void build_h(heap* h, const void* arr, size_t num, size_t size,
                int (*cmp)(const void*, const void*)) {
  h->sizeElement = size;
  h->size = num;
  h->compare = cmp;
  h->capacity = (h->size + 1) * 2;
  h->data = malloc(h->capacity * h->sizeElement);
  memcpy(h->data, arr, h->size * h->sizeElement);

  size_t i = (h->size - 1) / 2;
  while (true) {
    update_h(h, i); 
    if (i == 0) {
      break;
    }
    --i;
  }
}
void clean_h(heap* h) {
  free(h->data);
}

void push_h(heap* h, const void* data) {
  if (h->size == 0) {
    build_h(h, data, 1, h->sizeElement, h->compare);
    return ;
  }
  if (h->size == h->capacity) {
    update_capacity_h(h);
  }
  size_t i = h->size++;
  memcpy(h->data + i * h->sizeElement, data, h->sizeElement);
  while (true) {
    update_h(h, i);
    if (i == 0) {
      break;
    }
    i = (i - 1) / 2;
  }
}

void pop_h(heap* h) {
  if (h->size == 0) {
    return ;
  }
  size_t i = --h->size;
  memswap(h->data, h->data + i * h->sizeElement, h->sizeElement);
  i = 0;
  while (i < h->size) {
    i = update_h(h, i);
  }
}

void* top_h(heap* h) {
  if (h->size == 0) {
    return NULL;
  }
  return h->data;
}
