#include "compressor.hpp"
#include "bit_writer.hpp"
#include "bor.hpp"

#include <fstream>

static std::string readFileLineByLine(const std::string& filename) {
    std::ifstream file(filename);
    std::string content, line;
    while (std::getline(file, line)) {
        content += line + "\n";
    }
    return content;
}

Compressor::Compressor(const std::string& filename) : text_(readFileLineByLine(filename)) {}

std::ofstream& operator<<(std::ofstream& ofs, const Compressor& comp) {
  Tbor bor(comp.text_);
  ofs << bor;
  BitWriter bw;
  for (const char& ch : comp.text_) {
    bw.write(bor[ch]);
  }
  ofs.write(reinterpret_cast<const char*>(bw.data()), bw.size());
  return ofs;
}
