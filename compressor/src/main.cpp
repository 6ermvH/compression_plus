#include <iostream>
#include <string>

#include "bor.hpp"
#include "compressor.hpp"

void printUsage() {
  std::cerr << "Usage: ./main <input_file> <output_file>" << std::endl;
  std::cerr << "  or   ./main --help to show this help" << std::endl;
}

int main(int argc, char* argv[]) {
  // Check arguments
  if (argc == 2 && std::string(argv[1]) == "--help") {
    printUsage();
    return 0;
  }
  
  if (argc != 3) {
    std::cerr << "Error: Wrong number of arguments!" << std::endl;
    printUsage();
    return 1;
  }
  
  std::string inputFile = argv[1];
  std::string outputFile = argv[2];
  
  try {
    std::ofstream file(outputFile);
    if (!file.is_open()) {
      std::cerr << "Error: Could not open output file: " << outputFile << std::endl;
      return 1;
    }
    
    file << Compressor(inputFile);
    std::cout << "Successfully compressed " << inputFile << " to " << outputFile << std::endl;
  } catch (const std::exception& e) {
    std::cerr << "Error during compression: " << e.what() << std::endl;
    return 1;
  }
  
  return 0;
}
