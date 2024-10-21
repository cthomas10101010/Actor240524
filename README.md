# actor240524

This project started as an analysis and simulation of the cyber tactics used by APT Group Actor240524, focusing on attack processes, adversarial techniques, and payload delivery methods. Over time, it evolved significantly, now incorporating dynamic payload delivery via native Windows APIs, shellcode downloading, and execution, along with additional anti-analysis and persistence mechanisms.

The current version aims to simulate real-world adversary behaviors more accurately.

## compilation-command

```bash
g++ -Wall -Iinclude -std=c++17 -o Actor240524.exe src/main.cpp src/ABCloader.cpp src/ABCsync.cpp src/AntiAnalysis.cpp src/Communication.cpp src/Encryption.cpp src/Persistence.cpp src/ProcessFileHandling.cpp src/ShellcodeLoader.cpp -lws2_32 -lwininet -lntdll


🌟 major-changes 🌟
Originally, this project focused on DLL-based payload execution. The following major improvements have been made:

dynamic-shellcode-execution
The ShellcodeLoader module now dynamically downloads shellcode from a C2 server and executes it in memory using native Windows APIs like NtAllocateVirtualMemory and NtProtectVirtualMemory. This mimics real-world tactics to avoid traditional disk-based malware detection.

expanded-anti-analysis-techniques
Additional runtime checks prevent execution in analysis environments, including checks for screen resolution, process count, and debugger detection via PEB analysis and hardware breakpoints.

persistence-via-com-hijacking
The project simulates persistence by replacing system DLLs using COM hijacking techniques.

These updates transform the project into a comprehensive and realistic tool for analyzing adversarial techniques.

📜 contents
actor240524
compilation-command
🌟 major-changes 🌟
dynamic-shellcode-execution
expanded-anti-analysis-techniques
persistence-via-com-hijacking
