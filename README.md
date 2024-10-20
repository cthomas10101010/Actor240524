# APT Group Actor240524: Cyber Tactics Against Azerbaijan and Israel

## Overview
compile comand g++ -Wall -Iinclude -std=c++17 -o Actor240524.exe src/main.cpp src/ABCloader.cpp src/ABCsync.cpp src/AntiAnalysis.cpp src/Communication.cpp src/Encryption.cpp src/Persistence.cpp src/ProcessFileHandling.cpp -lws2_32 

This project analyzes and simulates the cyber tactics used by APT Group Actor240524, with a focus on the attack process, adversarial techniques, and payload delivery used in their campaign targeting Azerbaijan and Israel.

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
