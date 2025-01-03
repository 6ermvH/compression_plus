#ifndef NODE_H_INCLUDE
#define NODE_H_INCLUDE

#include <stddef.h>

typedef struct NODE {
  size_t count;
  char symbol;
  struct NODE* left;
  struct NODE* right;
} borNode;

borNode* make_node(size_t c, char sym, borNode* l, borNode* r);
int isTerminate(borNode* current);

#endif // NODE_H_INCLUDE
