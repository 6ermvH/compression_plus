#include "node.h"

#include <stdlib.h>

borNode* make_node(size_t c, char sym, borNode* l, borNode* r) {
  borNode* result = malloc(sizeof(borNode));
  result->count = c;
  result->symbol = sym;
  result->left = l;
  result->right = r;
}

int isTerminate(borNode* current) {
  return current->symbol - '\0';
}
