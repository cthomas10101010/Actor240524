#include <windows.h>
#include <psapi.h>
#include <iostream>
#include <vector>
#include "AntiAnalysis.h"

// Custom PEB definition (minimal version)
typedef struct _PEB {
    BYTE Reserved1[2];
    BYTE BeingDebugged;  // The field that tells if a debugger is present
    BYTE Reserved2[1];
    PVOID Reserved3[2];
    PVOID Ldr;
    PVOID ProcessParameters;
} PEB;

// Method to check screen resolution
bool AntiAnalysis::checkScreenResolution() {
    std::vector<std::pair<int, int>> validResolutions = {
        {1920, 1080}, {2560, 1440}, {3840, 2160}, {1280, 720}, {1366, 768}, {1600, 900}
    };

    // Get the screen resolution
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    // Print the resolution for debugging purposes
    std::cout << "[*] Detected screen resolution: " << screenWidth << "x" << screenHeight << std::endl;

    for (const auto& res : validResolutions) {
        if (screenWidth == res.first && screenHeight == res.second) {
            return true;  // Resolution matches a valid one
        }
    }

    std::cout << "[!] Suspicious screen resolution detected!" << std::endl;
    return false;  // Invalid resolution
}

// Method to check the number of processes
bool AntiAnalysis::checkProcessCount() {
    DWORD aProcesses[1024], cbNeeded, cProcesses;

    if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded)) {
        std::cerr << "[!] Failed to enumerate processes!" << std::endl;
        return false;
    }

    // Calculate the number of processes
    cProcesses = cbNeeded / sizeof(DWORD);

    std::cout << "[*] Detected " << cProcesses << " running processes." << std::endl;

    if (cProcesses < 200) {
        std::cout << "[!] Too few processes, possible sandbox detected!" << std::endl;
        return false;
    }

    return true;
}

// Method to check if a debugger is present
bool AntiAnalysis::checkDebugger() {
    // Accessing the PEB using the built-in __readgsqword function from Windows headers
    PEB* ProcessEnvironmentBlock = (PEB*)__readgsqword(0x60);

    // Check if the process is being debugged
    if (ProcessEnvironmentBlock->BeingDebugged == 1) {
        std::cout << "[!] Debugger detected!" << std::endl;
        return true;
    }

    return false;
}
