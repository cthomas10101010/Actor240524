#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <string>

class Encryption {
public:
    // Public method to decrypt and write data
    bool decryptDataAndWrite(const std::string& filePath);

    // Public method to decrypt and load DLLs
    bool decryptAndLoadDLL(const std::string& basePath);

private:
    // Private method to handle decryption
    std::string decrypt(const std::string& encryptedData);
};

#endif  // ENCRYPTION_H
