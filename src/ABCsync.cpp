#include "ABCsync.h"
#include <cstdlib>  // For system()
#include <iostream>

void ABCsync::executePayload() {
    std::string command = "calc.exe";  // For testing, we will open Calculator

    std::cout << "[*] ABCsync: Executing payload (opening Calculator)..." << std::endl;

    int result = system(command.c_str());

    if (result != 0) {
        std::cerr << "[!] ABCsync: Failed to execute payload (Calculator)." << std::endl;
    } else {
        std::cout << "[*] ABCsync: Payload (Calculator) executed successfully." << std::endl;
    }
}
