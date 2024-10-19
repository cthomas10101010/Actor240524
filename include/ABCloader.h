#ifndef ABCLOADER_H
#define ABCLOADER_H

#include <string>

class ABCloader {
public:
    void runLoader();  // Runs the loader functionality
private:
    bool decryptAndLoadPayload();  // Decrypts and loads the payload
    bool processHollowing(const std::string& targetProcess);  // Implements process hollowing
    unsigned long hashFileName(const std::wstring& fileName);  // Hashes the file name to get the unique ID
};

#endif // ABCLOADER_H
