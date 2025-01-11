#include "bor.hpp"

#include <stdexcept>

Tbor::Tbor(const std::unordered_map<char, std::size_t>& letters) {

  if (letters.empty()) {
    throw std::runtime_error("bad text");
  }
  
  std::priority_queue<Node*, std::vector<Node*>, compare_node> heap;
  for (const auto& pr : letters) {
    heap.push(new Node(nullptr, nullptr, pr.first, pr.second, true));
  }

  while (heap.size() > 1) {
    Node* lhs = heap.top();
    heap.pop();
    Node* rhs = heap.top();
    heap.pop();
    heap.push(new Node(lhs, rhs, '\0', lhs->num + rhs->num, false));
  }

  root = heap.top();
}

Tbor::Tbor(const std::string& text) : Tbor(text_to_tokens(text)) {}

Tbor::~Tbor() {
  dfs(root, delete_node);
}

std::unordered_map<char, std::size_t> Tbor::text_to_tokens(const std::string& text) {
  std::unordered_map<char, std::size_t> tokens;
  for (const char& symbol : text) {
    ++tokens[symbol];
  }
  return tokens;
}

void Tbor::dfs(Node* current, std::function<void(Node*)> op) {
  if (!current) {
    return ;
  }
  dfs(current->left, op);
  dfs(current->right, op);
  op(current);
}

void Tbor::delete_node(Node* current) {
  delete current;
}
