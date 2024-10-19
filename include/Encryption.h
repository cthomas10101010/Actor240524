#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <string>

class Encryption {
public:
    bool encrypt(const std::string& plaintext, const std::string& key, std::string& ciphertext);
    bool decrypt(const std::string& ciphertext, const std::string& key, std::string& plaintext);
};

#endif
