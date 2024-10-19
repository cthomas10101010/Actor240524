#include "ABCloader.h"
#include "Encryption.h"
#include <iostream>

// Function to run the loader
bool ABCloader::runLoader() {
    Encryption encryption;
    std::string filePath = "C:\\Users\\Public\\Documents\\decrypted_output.txt";  // Example path for decrypted output

    std::cout << "[*] Running ABCloader..." << std::endl;

    // Decrypt and write the data using the encryption module
    if (!encryption.decryptDataAndWrite(filePath)) {
        std::cerr << "[!] Failed to decrypt and write data!" << std::endl;
        return false;
    }

    std::cout << "[*] Decrypted data written to: " << filePath << std::endl;
    return true;
}
