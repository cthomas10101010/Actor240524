#include "Encryption.h"
#include <iostream>

std::string decrypt(const std::string& encryptedData) {
    std::cout << "[*] Simulating decryption of data..." << std::endl;

    // In real case, decryption would happen here, for example using AES
    // Here we mock decryption by returning a simple hardcoded string
    if (encryptedData == "fake_encrypted_payload") {
        return "calc.exe";  // Simulated decrypted payload
    }

    std::cerr << "[!] Decryption failed: unknown data!" << std::endl;
    return "";
}
