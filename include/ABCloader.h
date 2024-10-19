#ifndef ABCLOADER_H
#define ABCLOADER_H

#include <string>

class ABCloader {
public:
    void runLoader();
private:
    bool checkEnvironment();
    void decryptPayload();
    void loadDLL(const std::string& dllName);
};

#endif
