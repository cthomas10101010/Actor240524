#include "Encryption.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <filesystem>  // C++17 filesystem for directory handling

namespace fs = std::filesystem;

// Simulated decryption function
std::string Encryption::decrypt(const std::string& encryptedData) {
    // Simulate decryption by reversing the string
    std::string decryptedData = encryptedData;
    std::reverse(decryptedData.begin(), decryptedData.end());
    return decryptedData;
}

// Public method to decrypt and write data to a file
bool Encryption::decryptDataAndWrite(const std::string& filePath) {
    std::string encryptedPayload = "Encrypted Data";

    // Decrypt the payload
    std::string decryptedPayload = decrypt(encryptedPayload);

    // Ensure the directory exists
    fs::path directoryPath = fs::path(filePath).parent_path();
    if (!fs::exists(directoryPath)) {
        std::cout << "[*] Creating directory: " << directoryPath << std::endl;
        fs::create_directories(directoryPath);  // Creates the directory if it doesn't exist
    }

    // Simulate writing the decrypted data to the file
    std::ofstream outFile(filePath);
    if (!outFile) {
        std::cerr << "[!] Failed to open file for writing: " << filePath << std::endl;
        return false;
    }
    outFile << decryptedPayload;
    outFile.close();

    std::cout << "[*] Decrypted data written to " << filePath << std::endl;
    return true;
}

// Public method to decrypt and load DLLs
bool Encryption::decryptAndLoadDLL(const std::string& basePath) {
    // Simulated DLL decryption
    std::string encryptedDll1 = "vcruntime220.dll_encrypted";
    std::string encryptedDll2 = "vcruntime190.dll_encrypted";

    std::string decryptedDll1 = decrypt(encryptedDll1);
    std::string decryptedDll2 = decrypt(encryptedDll2);

    // Ensure the base directory exists
    fs::path directoryPath = fs::path(basePath);
    if (!fs::exists(directoryPath)) {
        std::cout << "[*] Creating directory: " << directoryPath << std::endl;
        fs::create_directories(directoryPath);  // Creates the directory if it doesn't exist
    }

    // Simulate writing DLLs to the filesystem
    std::ofstream dll1File(basePath + "\\vcruntime220.dll");
    std::ofstream dll2File(basePath + "\\vcruntime190.dll");

    if (!dll1File || !dll2File) {
        std::cerr << "[!] Failed to write decrypted DLLs." << std::endl;
        return false;
    }

    dll1File << decryptedDll1;
    dll2File << decryptedDll2;

    dll1File.close();
    dll2File.close();

    std::cout << "[*] Decrypted DLLs written to " << basePath << std::endl;
    return true;
}
