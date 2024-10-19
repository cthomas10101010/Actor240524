#include "ABCsync.h"
#include <iostream>
#include <windows.h>

bool ABCsync::executePayload() {
    std::cout << "[*] Executing the payload (launching Calculator)..." << std::endl;

    // Simulate executing the decrypted payload (open Calculator)
    if (ShellExecute(NULL, "open", "calc.exe", NULL, NULL, SW_SHOW) <= (HINSTANCE)32) {
        std::cerr << "[!] Failed to execute payload!" << std::endl;
        return false;
    }

    std::cout << "[*] Payload executed successfully!" << std::endl;
    return true;
}
