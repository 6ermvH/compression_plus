#include "bor.hpp"
#include "bit_writer.hpp"

#include <stdexcept>
#include <fstream>

Tbor::Tbor(const std::unordered_map<char, std::size_t>& letters) {

  if (letters.empty()) {
    throw std::runtime_error("bad text");
  }
  
  std::priority_queue<Node*, std::vector<Node*>, compare_node> heap;
  for (const auto& pr : letters) {
    heap.push(new Node(nullptr, nullptr, pr.first, pr.second));
  }

  while (heap.size() > 1) {
    Node* lhs = heap.top();
    heap.pop();
    Node* rhs = heap.top();
    heap.pop();
    heap.push(new Node(lhs, rhs, std::nullopt, lhs->num + rhs->num));
  }

  root_ = heap.top();
}

Tbor::Tbor(const std::string& text) : Tbor(text_to_tokens(text)) {
  dfs(root_, std::vector<bool>());
}

Tbor::~Tbor() {
  dfs(root_, delete_node);
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

void Tbor::dfs(Node* current, std::vector<bool> bits) {
  if (current->symbol.has_value()) {
    keyChars_[current->symbol.value()] = bits;
    return ;
  }
  bits.push_back(true);
  dfs(current->left, bits);
  bits.back() = false;
  dfs(current->right, bits);
}

void Tbor::delete_node(Node* current) {
  delete current;
}

std::vector<bool> Tbor::get_preambule() const {
  std::vector<bool> result;
  std::queue<Node*> q;
  q.push(root_);
  while (!q.empty()) {
    Node* current = q.front();
    q.pop();
    if (current->left) {
      result.push_back(1);
      q.push(current->left);
    } else {
      result.push_back(0);
    }
    if (current->right) {
      result.push_back(1);
      q.push(current->right);
    } else {
      result.push_back(0);
    }
  }
  return result;
}

std::vector<char> Tbor::get_alphabet() const {
  std::vector<char> result;
  std::queue<Node*> q;
  q.push(root_);
  while (!q.empty()) {
    Node* current = q.front();
    q.pop();
    if (!current->left && !current->right) {
      result.push_back(current->symbol.value());
    }
    if (current->left) {
      q.push(current->left);
    }
    if (current->right) {
      q.push(current->right);
    }
  }
  return result;
}

#include <iostream>

std::ofstream& operator<<(std::ofstream& ofs, const Tbor& bor) {
  {
    std::vector<char> alphabet = bor.get_alphabet();
    std::cout << '\n';
    std::size_t size = alphabet.size();
    ofs.write(reinterpret_cast<const char*>(&size), sizeof(int));
    ofs.write(reinterpret_cast<const char*>(alphabet.data()), alphabet.size());
  }
  {
    BitWriter bw;
    bw.write(bor.get_preambule());
    const char* data = reinterpret_cast<const char*>(bw.data());
    std::size_t size = bw.size();
    ofs.write(reinterpret_cast<const char*>(&size), sizeof(int));
    ofs.write(data, bw.size());
  }
  return ofs;
}
