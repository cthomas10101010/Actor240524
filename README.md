# Actor240524

This project started as an analysis and simulation of the cyber tactics used by APT Group Actor240524, focusing on attack processes, adversarial techniques, and payload delivery methods. Over time, it evolved significantly, now incorporating dynamic payload delivery via native Windows APIs, shellcode downloading, and execution, along with anti-analysis and persistence mechanisms.

The current version aims to simulate real-world adversary behaviors more accurately.

## Compilation Command

```bash
g++ -Wall -Iinclude -std=c++17 -o Actor240524.exe src/main.cpp src/ABCloader.cpp src/ABCsync.cpp src/AntiAnalysis.cpp src/Communication.cpp src/Encryption.cpp src/Persistence.cpp src/ProcessFileHandling.cpp src/ShellcodeLoader.cpp -lws2_32 -lwininet -lntdll
🌟 Major Changes 🌟
Originally, this project focused on DLL-based payload execution. The following major improvements have been made:

Dynamic Shellcode Execution: The ShellcodeLoader module now dynamically downloads shellcode from a C2 server and executes it in memory using native Windows APIs like NtAllocateVirtualMemory and NtProtectVirtualMemory. This mimics real-world tactics to avoid traditional disk-based malware detection.

Expanded Anti-Analysis Techniques: Additional runtime checks prevent execution in analysis environments, including checks for screen resolution, process count, and debugger detection via PEB analysis and hardware breakpoints.

Persistence via COM Hijacking: The project simulates persistence by replacing system DLLs using COM hijacking techniques.

These updates transform the project into a comprehensive and realistic tool for analyzing adversarial techniques.

📜 Contents
Overview
🌟 Major Changes 🌟
Installation
Usage
Modules
Technical Details
Adversarial Techniques
Disclaimer
🛠️ Installation
Clone the repository:

bash
Copy code
git clone https://github.com/your-username/Actor240524.git
cd Actor240524
Compile the project using the provided Makefile or the following command:

bash
Copy code
g++ -Wall -Iinclude -std=c++17 -o Actor240524.exe src/main.cpp src/ABCloader.cpp src/ABCsync.cpp src/AntiAnalysis.cpp src/Communication.cpp src/Encryption.cpp src/Persistence.cpp src/ProcessFileHandling.cpp src/ShellcodeLoader.cpp -lws2_32 -lwininet -lntdll
Run the program:

bash
Copy code
./Actor240524
⚙️ Usage
This project simulates the behavior observed in APT Group Actor240524’s campaigns. Key steps include:

Loader Execution: Uses ABCloader to decrypt and dynamically load DLLs or shellcode.
Shellcode Download & Execution: Downloads and executes shellcode from a remote C2 server, using native Windows API calls for memory allocation and execution.
Anti-Analysis Techniques: Implements checks like screen resolution, process count, PEB detection, and hardware breakpoints to avoid analysis environments.
Persistence Mechanisms: Uses COM hijacking to replace legitimate DLLs with malicious versions, maintaining persistence.
📦 Modules
ABCloader: Handles decryption and environment checks before loading malicious DLLs or shellcode.
ABCsync: Executes attack payloads, including file exfiltration, remote command execution, and C2 server communication.
AntiAnalysis: Implements anti-analysis techniques to evade detection, including PEB and hardware breakpoint detection.
ShellcodeLoader: Downloads and executes shellcode from a remote C2 server using native Windows APIs.
Network Communication: Encrypts and decrypts communication with the C2 server using AES-256 encryption.
Persistence: Implements COM hijacking to replace legitimate DLLs for persistence across system reboots.
ProcessFileHandling: Manages process interaction and file I/O for malicious activities.
🧑‍💻 Technical Details
This project is built using C++ and follows a modular, object-oriented design to ensure flexibility and ease of maintenance. Each component is designed to operate independently, allowing for easy updates and integration of additional adversarial techniques in the future.

Requirements
C++17
WinINet (for network communication)
NTDLL (for memory allocation and protection)
OpenSSL (for AES-256 encryption, if used in later versions)
Linux or Windows (with MinGW for Windows builds)
🔍 Adversarial Techniques
The following adversarial techniques are incorporated based on the observed behavior of APT Group Actor240524:

Native API Usage: Utilizes low-level Windows API functions like NtAllocateVirtualMemory and NtProtectVirtualMemory to dynamically allocate and execute shellcode, reducing detection.
String Encryption: Encrypts critical strings and API function names to avoid detection by static analysis tools.
PEB Detection: Detects the presence of debugging environments by analyzing PEB (Process Environment Block) fields.
Hardware Breakpoint Detection: Identifies active hardware breakpoints, typically set by debuggers.
COM Hijacking: Maintains persistence by replacing system DLLs with malicious ones, allowing the malware to survive system reboots.
⚠️ Disclaimer
This project is for academic and research purposes only. Any misuse of this code for unauthorized activities is strictly prohibited. The developers are not responsible for any malicious use of this project. Use it only in legal environments, such as penetration testing labs, where you have explicit permission.
