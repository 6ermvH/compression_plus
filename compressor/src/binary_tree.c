#include "binary_tree.h"

#include "heap.h"

#include <stddef.h>
#include <string.h>
#include <stdlib.h>

int node_compare(const void* lhs, const void* rhs) {
  const borNode* l = (const borNode*)lhs;
  const borNode* r = (const borNode*)rhs;
  return l->count - r->count;
}

void clean_node(borNode* node) {
  free(node);
}

void init_tree(b_tree* t, borNode* arr, size_t num) {
  heap h;
  build_h(&h, arr, num, sizeof(borNode), node_compare);
  while (h.size != 1) {
    borNode* r1 = malloc(sizeof(borNode));
    memcpy(r1, top_h(&h), sizeof(borNode));
    pop_h(&h);
    borNode* r2 = malloc(sizeof(borNode));
    memcpy(r2, top_h(&h), sizeof(borNode));
    pop_h(&h);
    push_h(&h, make_node(r1->count + r2->count, '\0', r1, r2));
  }
  t->root = malloc(sizeof(borNode));
  memcpy(t->root, top_h(&h), sizeof(borNode));
  clean_h(&h);
}

void clean_tree(b_tree* t) {
  dfs(t->root, clean_node);
}

void dfs(borNode* current, void (*op)(borNode*)) {
  if (current == NULL) {
    return ;
  }
  dfs(current->left, op);
  dfs(current->right, op);
  op(current);
}
