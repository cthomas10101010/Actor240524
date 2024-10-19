#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <string>

class Communication {
public:
    void establishConnection(const std::string& ip, int port);
};

#endif
