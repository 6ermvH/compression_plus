#include "bit_writer.hpp"

void BitWriter::write(const std::vector<bool>& bits) {
    for (bool bit : bits) {
        buffer |= (bit << bit_position);
        if (++bit_position == 8) {
            flush_byte();
        }
    }
}

const uint8_t* BitWriter::data() {
    if (bit_position > 0) {
        flush_byte();
    }
    align_to_4_bytes();
    return storage.data();
}

size_t BitWriter::size() const { return storage.size(); }

void BitWriter::flush_byte() {
    storage.push_back(buffer);
    buffer = 0;
    bit_position = 0;
}

void BitWriter::align_to_4_bytes() {
    while (storage.size() % 4 != 0) {
        storage.push_back(0);
    }
}
