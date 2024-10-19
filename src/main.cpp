#include <iostream>
#include "AntiAnalysis.h"

int main() {
    AntiAnalysis antiAnalysis;

    std::cout << "[*] Running anti-analysis techniques..." << std::endl;

    // Check for screen resolution
    if (!antiAnalysis.checkScreenResolution()) {
        std::cout << "[!] Exiting due to suspicious screen resolution!" << std::endl;
        return -1;
    }

    // Check for the number of processes
    if (!antiAnalysis.checkProcessCount()) {
        std::cout << "[!] Exiting due to suspicious process count!" << std::endl;
        return -1;
    }

    // Check if a debugger is attached
    if (antiAnalysis.checkDebugger()) {
        std::cout << "[!] Exiting due to debugger detection!" << std::endl;
        return -1;
    }

    std::cout << "[*] No debugger detected. Proceeding..." << std::endl;

    // Proceed with other operations
    return 0;
}
