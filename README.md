## Overview

```bash
g++ -Wall -Iinclude -std=c++17 -o Actor240524.exe src/main.cpp src/ABCloader.cpp src/ABCsync.cpp src/AntiAnalysis.cpp src/Communication.cpp src/Encryption.cpp src/Persistence.cpp src/ProcessFileHandling.cpp src/ShellcodeLoader.cpp -lws2_32 -lwininet -lntdll
This project analyzes and simulates the cyber tactics used by APT Group Actor240524, with a focus on the attack process, adversarial techniques, and payload delivery methods observed in their campaigns. The project has grown to integrate new functionalities, such as downloading and executing shellcode via native Windows APIs, which adds flexibility and stealth to the payload delivery process.

Contents
Overview
Installation
Usage
Modules
Technical Details
Adversarial Techniques
Disclaimer
Installation
Clone this repository:

bash
Copy code
git clone https://github.com/your-username/Actor240524.git
cd Actor240524
Compile the project using the provided Makefile or the command below:

bash
Copy code
g++ -Wall -Iinclude -std=c++17 -o Actor240524.exe src/main.cpp src/ABCloader.cpp src/ABCsync.cpp src/AntiAnalysis.cpp src/Communication.cpp src/Encryption.cpp src/Persistence.cpp src/ProcessFileHandling.cpp src/ShellcodeLoader.cpp -lws2_32 -lwininet -lntdll
Run the program:

bash
Copy code
./Actor240524
Usage
This project simulates the malware behavior observed in APT Group Actor240524's campaigns. The following steps are replicated:

Loader Execution: Uses ABCloader to decrypt and load DLLs or shellcode dynamically.
Shellcode Download & Execution: Dynamically downloads and executes shellcode from a remote C2 server, using native Windows API calls for memory allocation and execution.
Anti-Analysis Techniques: Implements checks like screen resolution validation, process count validation, PEB detection, and hardware breakpoints to avoid detection.
Persistence Mechanisms: Uses COM hijacking to maintain persistence by replacing legitimate system DLLs with malicious ones.
Modules
ABCloader: Manages decryption and environment checks before loading malicious DLLs or shellcode.
ABCsync: Executes attack payloads, including file exfiltration, remote command execution, and communication with the C2 server.
AntiAnalysis: Implements anti-analysis techniques such as PEB detection and hardware breakpoint identification to evade detection.
ShellcodeLoader: A new module that downloads and executes shellcode from a remote C2 server, leveraging native Windows APIs (NtAllocateVirtualMemory, NtProtectVirtualMemory).
Network Communication: Encrypts and decrypts communication with the C2 server using AES-256 encryption to secure the data exchange.
Persistence: Implements COM hijacking to replace legitimate DLLs for maintaining persistence across system reboots.
ProcessFileHandling: Manages process interaction and file I/O for malicious activities.
Technical Details
This project is built using C++ and follows a modular, object-oriented design to ensure flexibility and ease of maintenance. Each component of the project is designed to operate independently, allowing for easy updates and integration of additional adversarial techniques in the future.

Requirements
C++17
WinINet (for network communication)
NTDLL (for memory allocation and protection)
OpenSSL (for AES-256 encryption, if used in later versions)
Linux or Windows (with MinGW for Windows builds)
Adversarial Techniques
The following adversarial techniques are incorporated based on the observed behavior of APT Group Actor240524:

Native API Usage: Uses low-level Windows API functions such as NtAllocateVirtualMemory and NtProtectVirtualMemory to dynamically allocate and execute shellcode, reducing detection.
String Encryption: Encrypts critical strings and API function names to avoid detection by static analysis tools.
PEB Detection: Detects the presence of debugging environments by analyzing PEB (Process Environment Block) fields.
Hardware Breakpoint Detection: Identifies active hardware breakpoints that are typically set by debuggers.
COM Hijacking: Maintains persistence by replacing system DLLs with malicious ones, allowing the malware to survive system reboots.
Disclaimer
This project is for academic and research purposes only. Any misuse of this code for unauthorized activities is strictly prohibited. The developers are not responsible for any malicious use of this project. Use it only in legal environments, such as penetration testing labs, where you have explicit permission.

javascript
Copy code

### How to Add it to Your Repository:

1. Save this text as `README.md` in the root directory of your project.
2. Add it to your repository:
    ```bash
    git add README.md
    ```
3. Commit the changes:
    ```bash
    git commit -m "Add README with project documentation"
    ```
4. Push it to GitHub:
    ```bash
    git push origin main
    ```

This will display the formatted documentation on the main page of your GitHub repository.

Let me know if you need further assistance!





