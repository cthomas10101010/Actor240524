#include "AntiAnalysis.h"
#include <windows.h>
#include <iostream>

void AntiAnalysis::runAntiAnalysis() {
    std::cout << "[*] AntiAnalysis: Starting anti-analysis techniques..." << std::endl;

    if (checkPEB()) {
        std::cerr << "[!] AntiAnalysis: Debugger detected, exiting." << std::endl;
        exit(1);
    } else {
        std::cout << "[*] AntiAnalysis: No debugger detected." << std::endl;
    }

    if (!checkScreenResolution()) {
        std::cerr << "[!] AntiAnalysis: Sandbox environment detected, exiting." << std::endl;
        exit(1);
    } else {
        std::cout << "[*] AntiAnalysis: Screen resolution check passed." << std::endl;
    }

    if (!checkProcessCount()) {
        std::cerr << "[!] AntiAnalysis: Low process count, likely sandbox. Exiting..." << std::endl;
        exit(1);
    } else {
        std::cout << "[*] AntiAnalysis: Process count check passed." << std::endl;
    }
}

bool AntiAnalysis::checkPEB() {
    // PEB anti-debugging check (simulated)
    BOOL isDebugged = IsDebuggerPresent();
    return isDebugged;
}

bool AntiAnalysis::checkScreenResolution() {
    // Get screen resolution
    DEVMODE dm;
    EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &dm);
    
    int width = dm.dmPelsWidth;
    int height = dm.dmPelsHeight;

    std::cout << "[*] AntiAnalysis: Screen resolution: " << width << "x" << height << std::endl;

    // Check if resolution matches common virtual machine resolutions
    return !(width == 800 && height == 600);  // 800x600 is common in sandboxes
}

bool AntiAnalysis::checkProcessCount() {
    DWORD processCount = GetProcessCount();
    std::cout << "[*] AntiAnalysis: Number of processes: " << processCount << std::endl;

    return processCount >= 200;
}

DWORD AntiAnalysis::GetProcessCount() {
    DWORD aProcesses[1024], cbNeeded, cProcesses;
    if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded)) {
        return 0;
    }

    cProcesses = cbNeeded / sizeof(DWORD);
    return cProcesses;
}
