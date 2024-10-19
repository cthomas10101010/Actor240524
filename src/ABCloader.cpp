#include "ABCloader.h"
#include "Encryption.h"
#include <iostream>

bool ABCloader::runLoader() {
    Encryption encryption;
    std::string filePath = "C:\\Users\\Public\\Documents\\decrypted_output.txt";

    std::cout << "[*] Running ABCloader..." << std::endl;
    if (!encryption.decryptDataAndWrite(filePath)) {
        std::cerr << "[!] Failed to decrypt and write data!" << std::endl;
        return false;
    }

    std::cout << "[*] Decrypted data written to: " << filePath << std::endl;
    return true;
}
