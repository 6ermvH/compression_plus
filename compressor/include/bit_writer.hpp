#ifndef BITWRITER_H
#define BITWRITER_H

#include <vector>
#include <cstdint>

class BitWriter {
public:
    void write(const std::vector<bool>& bits);
    const uint8_t* data();
    size_t size() const;

private:
    void flush_byte();
    void align_to_4_bytes();

    std::vector<uint8_t> storage;
    uint8_t buffer = 0;
    uint8_t bit_position = 0;
};

#endif // BITWRITER_H

