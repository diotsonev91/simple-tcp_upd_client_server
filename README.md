🧪 Simple TCP & UDP Socket App in C
This is a minimal C application that demonstrates basic networking using TCP and UDP sockets. The same codebase allows switching between TCP and UDP mode using command-line arguments.

🔧 Features
Send and receive simple messages

Supports both TCP and UDP

Role switching: server or client

Command-line interface for easy testing

📦 Files
socket_app.c — source file with TCP/UDP server and client logic in one

🖥️ How to Build
bash
Copy
Edit
gcc socket_app.c -o socket_app
🚀 How to Run
TCP Mode
bash
Copy
Edit
# Terminal 1 (Server)
./socket_app server tcp

# Terminal 2 (Client)
./socket_app client tcp
UDP Mode
bash
Copy
Edit
# Terminal 1 (Server)
./socket_app server udp

# Terminal 2 (Client)
./socket_app client udp