#ifndef COMPRESSOR_H
#define COMPRESSOR_H

#include <string>
#include <fstream>

class Compressor {
public:
  Compressor(const std::string& filename);

  friend std::ofstream& operator<<(std::ofstream& ofs, const Compressor& comp);
private:
  std::string text_;
};

class DeCompressor {
public:
  DeCompressor(const std::string& filename);

  friend std::ifstream& operator>>(std::ifstream& is, const DeCompressor& decomp);
};

#endif // COMPRESSOR_H
