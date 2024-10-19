#include "Encryption.h"
#include <iostream>
#include <fstream>
#include <algorithm> // For std::reverse

std::string Encryption::decrypt(const std::string& encryptedData) {
    // Simulate decryption by reversing the string (just an example)
    std::string decryptedData = encryptedData;
    std::reverse(decryptedData.begin(), decryptedData.end());
    return decryptedData;
}

bool Encryption::decryptDataAndWrite(const std::string& filePath) {
    std::string decryptedData = "Decrypted content goes here";  // Example decrypted data

    std::ofstream outFile(filePath);
    if (!outFile.is_open()) {
        std::cerr << "[!] Failed to open file for writing: " << filePath << std::endl;
        return false;
    }

    outFile << decryptedData;
    outFile.close();

    std::cout << "[*] Decrypted data written to " << filePath << std::endl;
    return true;
}
