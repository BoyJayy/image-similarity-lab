#include <imgsim/sha256.hpp>
#include <openssl/evp.h>
#include <memory>
#include <fstream>
#include <stdexcept>
#include <cstdint>
#include <cstddef>
#include <array>


//tho i could be use SHA256_INIT but its too old now and docs recommend to use EVP
namespace imgsim { 
    sha256_hash_t sha256_file(const std::filesystem::path& path) {
        std::ifstream file(path, std::ios::binary);
        if (!file)
            throw std::runtime_error("Failed to open file: " + path.string());
        //EVP_MD_CTX - stores parts of sha256 (cuz our file can be too big to fit in ram)
        using ContextPtr = std::unique_ptr<EVP_MD_CTX, decltype(&EVP_MD_CTX_free)>; //decltype tho cuz delete ContextPtr doesnt work (use EVP_MD_CTX_free instead)
        ContextPtr ctx(EVP_MD_CTX_new(), &EVP_MD_CTX_free);
        if (!ctx)
            throw std::runtime_error("Failed to create EVP_MD_CTX");
        //ctx.get cuz requires normal pointer to EVP_MD_CTX not unique_ptr, nullptr is for openSSL engine (we dont use it)
        if (EVP_DigestInit_ex(ctx.get(), EVP_sha256(), nullptr) != 1) // SHA256 init
            throw std::runtime_error("Failed to initialize SHA256 context");
        std::array<char,1024*1024> buffer{}; //1MB buffer, we will feel it by parts
        while (file) {
            file.read(buffer.data(), static_cast<std::streamsize>(buffer.size()));
            const std::streamsize bytesRead = file.gcount();
            if (bytesRead > 0) {
                if (EVP_DigestUpdate(ctx.get(), buffer.data(), static_cast<std::size_t>(bytesRead)) != 1) // SHA256 update
                    throw std::runtime_error("Failed to update SHA256 hash");
            }

        }
        //check if we reached the end of the file, if not then there was an error reading the file
        if (!file.eof()) 
            throw std::runtime_error("Failed to read file: " + path.string());
        sha256_hash_t hash{};
        unsigned int hashLength = 0;
        if (EVP_DigestFinal_ex(ctx.get(), hash.data(), &hashLength) != 1) // SHA256 final
            throw std::runtime_error("Failed to finalize SHA256 hash");
        if (hashLength != static_cast<unsigned int>(SHA256_HASH_SIZE))
            throw std::runtime_error("Unexpected SHA256 hash length");
        return hash;
    }
}