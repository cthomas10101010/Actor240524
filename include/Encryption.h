#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <string>

class Encryption {
public:
    // Function to decrypt data and write it to a specified file path
    bool decryptDataAndWrite(const std::string& filePath);

private:
    // Function to decrypt the encrypted data (private helper function)
    std::string decrypt(const std::string& encryptedData);
};

#endif
