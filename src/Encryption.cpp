#include "Encryption.h"
#include <iostream>
#include <fstream>
#include <algorithm> // For std::reverse
#include <stdexcept>

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

std::string Encryption::encrypt(const std::string& data, const std::string& key) {
    // Placeholder encryption logic
    if (key != "AES256KEY") {
        throw std::invalid_argument("Invalid encryption key");
    }
    return "encrypted_" + data; // Simulated encryption
}

std::string Encryption::decrypt(const std::string& data, const std::string& key) {
    // Placeholder decryption logic
    if (key != "AES256KEY") {
        throw std::invalid_argument("Invalid decryption key");
    }
    return data.substr(10); // Simulated decryption
}