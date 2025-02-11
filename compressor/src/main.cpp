#include <iostream>

#include "bor.hpp"
#include "compressor.hpp"

int main() {

  std::ofstream file("example.edb");
  file << Compressor("example.txt");
}
