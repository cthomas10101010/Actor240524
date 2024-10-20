#include "Communication.h"
#include "Encryption.h"
#include <iostream>

void Communication::establishConnection(const std::string& ip, int port) {
    // Encrypt data using AES-256 before sending
    Encryption encryption;
    std::string data = "Hello C2";
    std::string encryptedData = encryption.encrypt(data, "AES256KEY");

    // Simulate sending UDP packet to C server
    std::cout << "Sending encrypted data to C2: " << encryptedData << std::endl;
}