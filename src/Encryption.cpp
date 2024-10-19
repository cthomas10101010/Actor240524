#include "Encryption.h"
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <cstring>
#include <iostream>

bool Encryption::encrypt(const std::string& plaintext, const std::string& key, std::string& ciphertext) {
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if (!ctx) return false;

    // Generate an initialization vector (IV)
    unsigned char iv[EVP_MAX_IV_LENGTH];
    if (!RAND_bytes(iv, EVP_MAX_IV_LENGTH)) {
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }

    // Key should be 32 bytes for AES-256
    unsigned char aes_key[32];
    std::memset(aes_key, 0, sizeof(aes_key));
    std::memcpy(aes_key, key.c_str(), std::min(key.size(), sizeof(aes_key)));

    // Initialize encryption context
    if (EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, aes_key, iv) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }

    int len;
    std::vector<unsigned char> ciphertext_buf(plaintext.size() + EVP_CIPHER_block_size(EVP_aes_256_cbc()));
    
    // Perform encryption
    if (EVP_EncryptUpdate(ctx, ciphertext_buf.data(), &len, (unsigned char*)plaintext.data(), plaintext.size()) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }

    int ciphertext_len = len;

    if (EVP_EncryptFinal_ex(ctx, ciphertext_buf.data() + len, &len) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }
    ciphertext_len += len;

    ciphertext = std::string((char*)iv, EVP_MAX_IV_LENGTH) + std::string((char*)ciphertext_buf.data(), ciphertext_len);

    EVP_CIPHER_CTX_free(ctx);
    return true;
}

bool Encryption::decrypt(const std::string& ciphertext, const std::string& key, std::string& plaintext) {
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if (!ctx) return false;

    // Split the IV and the ciphertext
    std::string iv = ciphertext.substr(0, EVP_MAX_IV_LENGTH);
    std::string actual_ciphertext = ciphertext.substr(EVP_MAX_IV_LENGTH);

    unsigned char aes_key[32];
    std::memset(aes_key, 0, sizeof(aes_key));
    std::memcpy(aes_key, key.c_str(), std::min(key.size(), sizeof(aes_key)));

    if (EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, aes_key, (unsigned char*)iv.c_str()) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }

    int len;
    std::vector<unsigned char> plaintext_buf(actual_ciphertext.size());

    if (EVP_DecryptUpdate(ctx, plaintext_buf.data(), &len, (unsigned char*)actual_ciphertext.data(), actual_ciphertext.size()) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }

    int plaintext_len = len;

    if (EVP_DecryptFinal_ex(ctx, plaintext_buf.data() + len, &len) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }
    plaintext_len += len;

    plaintext = std::string((char*)plaintext_buf.data(), plaintext_len);

    EVP_CIPHER_CTX_free(ctx);
    return true;
}
