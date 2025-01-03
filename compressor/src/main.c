#include "heap.h"

#include <stdio.h>
#include <stdlib.h>

int compare(const void* lhs, const void* rhs) {
  const int* l = (const int*)lhs;
  const int* r = (const int*)rhs;
  return *l - *r;
}

int main(void) {

  int a[] = {5, 2, 6, 4, 3, 1};

  heap h;
  build_h(&h, a, 6, sizeof(int), compare);

  printf("%ld\n", h.size);
  
  for (size_t i = 0; i < 3; ++i) {
    int* res = (int*)top_h(&h);
    printf("res : %d\n", *res);
    pop_h(&h);
  }

  int val = -3;
  push_h(&h, &val);
  int* res = (int*)top_h(&h);
  printf("res : %d\n", *res);

  clean_h(&h);


}
