#ifndef BINARY_TREE_H_INCLUDE
#define BINARY_TREE_H_INCLUDE

#include "node.h"

typedef struct TREE {
  borNode* root;
} b_tree;

void init_tree(b_tree* t, borNode* arr, size_t num);
void clean_tree(b_tree* t);

void dfs(borNode* current, void (*op)(borNode*));

#endif // BINARY_TREE_H_INCLUDE

