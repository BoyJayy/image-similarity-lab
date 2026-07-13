#pragma once
#include <cstdint>
#include <cstddef>
#include <vector>
#include <string.h>

namespace imgsim {
    //https://thealgorithms.github.io/C-Plus-Plus/d4/d08/sha256_8cpp.html
    struct sha256_buff {
        uint64_t data_size;
        uint32_t h[8];
        uint8_t last_chunk[64];
        uint8_t chunk_size;
    };
    void sha256_init(struct sha256_buff* buff);
    void sha256_update(struct sha256_buff* buff, const void* data, size_t size);
    void sha256_finalize(struct sha256_buff* buff);
    void sha256_read(const struct sha256_buff* buff, uint8_t* hash);
    void sha256_read_hex(const struct sha256_buff* buff, char* hex);
    void sha256_easy_hash(const void* data, size_t size, uint8_t* hash);
    void sha256_easy_hash_hex(const void* data, size_t size, char* hex);
    class SHA256 {
    private:
        struct sha256_buff buff;
    public:
        SHA256() {
            sha256_init(&buff);
        }
        
        void update(const void* data, std::size_t size) {
            sha256_update(&buff, data, size);
        }

        std::string hash() {
            char hash[64];
            sha256_finalize(&buff);
            sha256_read_hex(&buff, hash);
            sha256_init(&buff);
            return std::string(hash, 64);
        }
        
        static std::string hashString(const std::string& str) {
            char hash[64];
            sha256_easy_hash_hex(str.c_str(), str.length(), hash);
            return std::string(hash, 64);
        }
    };
}