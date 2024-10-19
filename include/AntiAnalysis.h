#ifndef ANTIANALYSIS_H
#define ANTIANALYSIS_H

class AntiAnalysis {
public:
    // Method to check screen resolution
    bool checkScreenResolution();

    // Method to check the number of processes
    bool checkProcessCount();

    // Method to check if a debugger is present
    bool checkDebugger();

    // New method to run all anti-analysis techniques
    bool runAntiAnalysis();  // Add this declaration
};

#endif  // ANTIANALYSIS_H
