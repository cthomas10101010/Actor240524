#ifndef ANTIANALYSIS_H
#define ANTIANALYSIS_H

class AntiAnalysis {
public:
    void runAntiAnalysis();
private:
    bool checkPEB();
    bool checkScreenResolution();
    bool checkProcessCount();
};

#endif
