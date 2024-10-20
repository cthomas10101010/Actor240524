APT Group Actor240524: Cyber Tactics Against Target Systems
This project analyzes and simulates the cyber tactics used by APT Group Actor240524, focusing on attack processes, adversarial techniques, and payload delivery during their campaign targeting sensitive systems. Below is the compilation command for the project, ensuring all components are linked correctly.

Overview
Compile the project with the following command:

bash
Copy code
g++ -Wall -Iinclude -std=c++17 -o Actor240524.exe src/main.cpp src/ABCloader.cpp src/ABCsync.cpp src/AntiAnalysis.cpp src/Communication.cpp src/Encryption.cpp src/Persistence.cpp src/ProcessFileHandling.cpp -lws2_32 
This project simulates malware behavior observed in APT Group Actor240524's campaign, replicating their tactics in a modular C++ program, including loader execution, payload deployment, anti-analysis mechanisms, and persistence techniques.

###Advanced Features for Later Experimentation:
Once you’re satisfied with the core functionality, the project can be enhanced by adding more sophisticated malware behaviors, advanced adversarial techniques, and encryption strategies. Here are some areas to explore:

1. Payload Encryption and Decryption
Current Status: In the current code, the payload is decrypted by ABCloader, which loads the necessary components to execute further attacks.
Experimentation: You could implement more complex encryption algorithms like RSA or hybrid cryptosystems, combining RSA and AES for asymmetric and symmetric encryption, respectively. Experiment with real-time encryption and decryption during execution for higher security in payload transmission.
2. Enhanced Anti-Analysis Techniques
Current Status: Basic anti-analysis techniques such as screen resolution checks and process count verification are in place.
Experimentation: Expand on this by introducing sandbox detection techniques, timing analysis to detect debuggers, or checking for the presence of virtualization software (VMWare, VirtualBox). You could also add memory-based integrity checks to ensure that critical sections of the malware code haven’t been tampered with.
3. Polymorphic Code
Experimentation: Polymorphic malware changes its code each time it runs, making it harder for static analysis to detect. You could experiment with dynamically altering portions of your code or key variables every time the program executes. This could be done by integrating polymorphism engines to encode parts of the malware and decoding them during runtime.
4. Fileless Persistence Mechanisms
Current Status: COM hijacking is used for persistence, replacing legitimate DLLs with malicious ones.
Experimentation: Try incorporating fileless persistence methods that leave little or no trace on the file system. Techniques like abusing Windows Registry or WMI (Windows Management Instrumentation) to maintain persistence without writing any files to the disk could be explored. This would involve storing the payload entirely in memory or within registry keys.
5. Dynamic API Hooking
Experimentation: Experiment with dynamic API hooking, where your malware intercepts API calls made by the operating system or other applications. This allows you to manipulate or hide certain actions, such as masking file operations, network communications, or process creations, making the malware more stealthy.
6. Stealth Network Communication
Current Status: Basic encrypted communication with the C2 server is implemented using AES-256.
Experimentation: You could try implementing steganography techniques for network communication, where payload data is hidden within images or other seemingly benign file types to evade detection by network security tools. Alternatively, experiment with using covert channels or encrypted peer-to-peer communication methods.
7. Obfuscation Techniques
Experimentation: Explore the use of obfuscation to hide the malware’s true intent and make reverse engineering difficult. This can be done by renaming functions, using complex control flows, or employing string encryption. Integrating a custom-built obfuscation layer into the build process could make the malware harder to analyze by both human and automated tools.
8. Kernel-Mode Components
Experimentation: For advanced exploration, try creating kernel-mode components (like rootkits) that can hide processes or files from the operating system, granting the malware more control and stealth. This requires a deep understanding of Windows kernel APIs and careful handling to avoid blue screens or system instability.

## Overview
compile comand g++ -Wall -Iinclude -std=c++17 -o Actor240524.exe src/main.cpp src/ABCloader.cpp src/ABCsync.cpp src/AntiAnalysis.cpp src/Communication.cpp src/Encryption.cpp src/Persistence.cpp src/ProcessFileHandling.cpp -lws2_32 

This project analyzes and simulates the cyber tactics used by APT Group Actor240524, with a focus on the attack process, adversarial techniques, and payload delivery used in their campaign targeting 

### Contents
- [Overview](#overview)
- [Installation](#installation)
- [Usage](#usage)
- [Modules](#modules)
- [Technical Details](#technical-details)
- [Adversarial Techniques](#adversarial-techniques)
- [Disclaimer](#disclaimer)

## Installation

1. Clone this repository:
    ```bash
    git clone https://github.com/your-username/Actor240524.git
    cd Actor240524
    ```

2. Compile the project using the provided `Makefile`:
    ```bash
    make all
    ```

3. Run the program:
    ```bash
    ./Actor240524
    ```

## Usage

This project simulates the malware behavior observed in APT Group Actor240524's campaign. The program replicates the following steps:

1. **Loader Execution**: Simulates the ABCloader, which decrypts and loads DLLs.
2. **Payload Execution**: Executes the ABCsync payload for remote command execution and file stealing.
3. **Anti-Analysis Techniques**: Includes PEB detection, hardware breakpoints, and screen resolution checks.
4. **Persistence Mechanisms**: COM hijacking to maintain persistence.

## Modules

1. **ABCloader**: Manages the decryption and environment checking before loading malicious DLLs.
2. **ABCsync**: Executes the attack payload, including file stealing, remote command execution, and communication with C2.
3. **AntiAnalysis**: Implements various anti-analysis techniques like PEB detection and hardware breakpoints.
4. **Network Communication**: Encrypts and decrypts communication with the C2 server using AES-256 encryption.
5. **Persistence**: Uses COM hijacking to replace legitimate DLLs for persistence.
6. **ProcessFileHandling**: Handles process interaction and file I/O.

## Technical Details

The project is implemented in C++ with a modular design. Each component follows the object-oriented programming paradigm for flexibility and maintainability.

### Requirements
- C++17
- OpenSSL (for AES-256 encryption)
- Linux or Windows (with MinGW)

## Adversarial Techniques

The following adversarial techniques are implemented based on the behavior of Actor240524:

- **API Encryption**: Critical strings are encrypted to avoid detection.
- **PEB Detection**: Detects debugging tools using PEB fields.
- **Hardware Breakpoint Detection**: Identifies debugging by checking for breakpoints.
- **COM Hijacking**: Achieves persistence by replacing system DLLs.

## Disclaimer

This project is for academic and research purposes only. Any misuse of this code is prohibited. The developers are not responsible for any malicious use of this project.
