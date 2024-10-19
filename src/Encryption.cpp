#include <iostream>
#include <fstream>
#include <filesystem>
#include <algorithm>  // for std::reverse
#include "Encryption.h"

// Mock decrypt function (just an example, you can modify this)
std::string Encryption::decrypt(const std::string& encryptedData) {
    // Simulate the decryption process by reversing the string (for example purposes)
    std::string decryptedData = encryptedData;
    std::reverse(decryptedData.begin(), decryptedData.end());
    return decryptedData;
}

bool Encryption::decryptDataAndWrite(const std::string& filePath) {
    // Simulate decryption process (for now, it's just writing dummy data)
    std::string decryptedData = "Decrypted payload data...";

    // Open a file to write the decrypted data
    std::ofstream outFile(filePath);
    if (!outFile) {
        std::cerr << "[!] Failed to open file for writing: " << filePath << std::endl;
        return false;
    }

    // Write the decrypted data to the file
    outFile << decryptedData;
    outFile.close();

    std::cout << "[*] Decrypted data written to " << filePath << std::endl;
    return true;
}