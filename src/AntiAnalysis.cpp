#include "AntiAnalysis.h"
#include <windows.h>
#include <iostream>
#include <psapi.h>

bool AntiAnalysis::checkScreenResolution() {
    // Get the screen resolution
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    std::cout << "[*] Detected screen resolution: " << screenWidth << "x" << screenHeight << std::endl;

    if (screenWidth < 800 || screenHeight < 600) {
        std::cout << "[!] Screen resolution too low. Potential sandbox detected." << std::endl;
        return false;  // Fail the check only for extremely low resolutions
    }

    return true;  // Pass the check otherwise
}

bool AntiAnalysis::checkProcessCount() {
    DWORD processes[1024], needed, processCount;
    if (!EnumProcesses(processes, sizeof(processes), &needed)) {
        std::cerr << "[!] Failed to enumerate processes." << std::endl;
        return false;
    }

    processCount = needed / sizeof(DWORD);
    std::cout << "[*] Detected " << processCount << " running processes." << std::endl;

    if (processCount < 200) {
        std::cerr << "[!] Too few processes. Potential sandbox detected." << std::endl;
        return false;
    }
    return true;
}
