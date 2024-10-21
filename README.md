# Actor240524

## Overview

This project initially began as a study of the tactics used by APT Group Actor240524, specifically focusing on their cyberattack processes, adversarial techniques, and payload delivery methods. The project has since evolved to incorporate additional features such as dynamic payload delivery via native Windows APIs, shellcode downloading, in-memory execution, and basic anti-analysis mechanisms.

The current version simulates some real-world adversarial behaviors, particularly emphasizing fileless malware techniques and anti-analysis checks.

### Contents
- [Overview](#overview)
- [Installation](#installation)
- [Usage](#usage)
- [Modules](#modules)
- [Technical Details](#technical-details)
- [Adversarial Techniques](#adversarial-techniques)
- [Disclaimer](#disclaimer)

---

## Installation

1. **Clone this repository**:
    ```bash
    git clone https://github.com/your-username/Actor240524.git
    cd Actor240524
    ```

2. **Compile the project** using the provided command:
    ```bash
    g++ -Wall -Iinclude -std=c++17 -o Actor240524.exe src/main.cpp src/ABCloader.cpp src/ABCsync.cpp src/AntiAnalysis.cpp src/Communication.cpp src/Encryption.cpp src/Persistence.cpp src/ProcessFileHandling.cpp src/ShellcodeLoader.cpp -lws2_32 -lwininet -lntdll
    ```

3. **Run the program**:
    ```bash
    ./Actor240524
    ```

---

## Usage

This project simulates basic behaviors observed in some APT campaigns. The program executes the following steps:

1. **Loader Execution**: Simulates the ABCloader, which decrypts and loads malicious code.
2. **Shellcode Execution**: Downloads and executes shellcode in memory from a remote server (C2 server), avoiding disk usage.
3. **Anti-Analysis Techniques**: Implements PEB detection, screen resolution, and process count checks to detect analysis environments.
4. **Basic Communication**: Communicates with a C2 server for potential command-and-control tasks (e.g., downloading shellcode).

---

## Modules

1. **ABCloader**: Manages decryption and environment checking before loading malicious DLLs or shellcode.
2. **ABCsync**: (Placeholder for future C2 communication) Could execute attack payloads like file exfiltration or remote commands.
3. **AntiAnalysis**: Implements anti-analysis techniques like PEB detection, screen resolution checks, and process count validation to avoid execution in analysis environments.
4. **ShellcodeLoader**: Downloads shellcode from a C2 server and executes it in memory using native Windows APIs like `NtAllocateVirtualMemory` and `NtProtectVirtualMemory`.
5. **Network Communication**: (Placeholder) Encrypts and decrypts communication with the C2 server using AES-256 encryption.
6. **ProcessFileHandling**: Manages file I/O for malicious activities (future scope).

---

## Technical Details

The project is implemented in C++ and designed with modularity in mind to allow flexibility for future enhancements. Each module is self-contained and interacts with others through well-defined interfaces.

### Requirements

- C++17
- OpenSSL (for AES-256 encryption)
- WinINet (for network communication)
- NTDLL (for memory allocation and protection)
- Linux or Windows (with MinGW for Windows builds)

---

## Adversarial Techniques

The following adversarial techniques are implemented based on common behaviors observed in APT campaigns:

- **Shellcode Execution**: The malware dynamically downloads and executes shellcode directly in memory, mimicking fileless malware techniques to avoid traditional disk-based detection.
- **API Encryption**: Placeholder for future use, could encrypt critical strings and API calls to avoid detection by static analysis tools.
- **PEB Detection**: Detects the presence of debugging tools by analyzing PEB (Process Environment Block) fields.
- **Anti-Debugging**: Includes checks like screen resolution and process count to detect analysis environments.

---

## Disclaimer

This project is for **academic and research purposes only**. Any misuse of this code for unauthorized activities is strictly prohibited. The developers are not responsible for any malicious use of this project. Ensure it is used only in legal environments such as penetration testing labs where explicit permission is granted.

---

## Explanation of Changes in `main.cpp`

The `main.cpp` file has undergone several updates as the project evolved from studying APT tactics to more advanced adversarial simulation:

1. **Dynamic Shellcode Execution**: The `ShellcodeLoader` module was introduced to dynamically download and execute shellcode in memory from a C2 server. This mimics real-world adversarial tactics by avoiding the use of disk-based storage for malware.

2. **Expanded Anti-Analysis Techniques**: The `AntiAnalysis` module includes runtime checks to detect analysis environments, such as verifying screen resolution and process counts, as well as PEB checks to detect debugging tools.

3. **Modular Design**: The project has been restructured into modular components (loader, shellcode execution, anti-analysis) for easier maintenance and potential future expansions, such as network communication or file exfiltration.

---

