#include <iostream>

#include "bor.hpp"

int main() {
  Tbor a("qwertyqsr");

  auto d = a.data();
  for (auto [key, value] : d) {
    std::cout << key << " : ";
    for (auto b : value) {
      std::cout << b << ' ';
    }
    std::cout << '\n';
  }
  for (auto b : a.get_preambule()) {
    std::cout << b << ' ';
  }
  std::cout << '\n';
  std::cout << (a.get_preambule() == std::vector<bool>{1, 1, 0, 1, 0, 0});
}
