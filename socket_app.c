
// Compile with: gcc socket_app.c -o socket_app
// Run server:   ./socket_app server tcp
// Run client:   ./socket_app client tcp

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8888
#define BUFFER_SIZE 1024

void run_tcp_server();
void run_tcp_client();
void run_udp_server();
void run_udp_client();

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s [server|client] [tcp|udp]\n", argv[0]);
        return 1;
    }

    int is_server = strcmp(argv[1], "server") == 0;
    int use_tcp = strcmp(argv[2], "tcp") == 0;

    if (is_server && use_tcp) run_tcp_server();
    else if (!is_server && use_tcp) run_tcp_client();
    else if (is_server && !use_tcp) run_udp_server();
    else run_udp_client();

    return 0;
}

// TCP SERVER
void run_tcp_server() {
    int sock, client_sock;
    struct sockaddr_in server, client;
    char buffer[BUFFER_SIZE];

    sock = socket(AF_INET, SOCK_STREAM, 0);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    bind(sock, (struct sockaddr *)&server, sizeof(server));
    listen(sock, 1);
    printf("TCP Server listening on port %d...\n", PORT);

    int c = sizeof(struct sockaddr_in);
    client_sock = accept(sock, (struct sockaddr *)&client, (socklen_t*)&c);
    recv(client_sock, buffer, BUFFER_SIZE, 0);
    printf("TCP Received: %s\n", buffer);
    send(client_sock, "Hello from TCP server!", 23, 0);
    close(client_sock);
    close(sock);
}

// TCP CLIENT
void run_tcp_client() {
    int sock;
    struct sockaddr_in server;
    char buffer[BUFFER_SIZE] = "Hello from TCP client!";

    sock = socket(AF_INET, SOCK_STREAM, 0);
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &server.sin_addr);

    connect(sock, (struct sockaddr *)&server, sizeof(server));
    send(sock, buffer, strlen(buffer), 0);
    recv(sock, buffer, BUFFER_SIZE, 0);
    printf("TCP Server replied: %s\n", buffer);
    close(sock);
}

// UDP SERVER
void run_udp_server() {
    int sock;
    struct sockaddr_in server, client;
    char buffer[BUFFER_SIZE];
    socklen_t len = sizeof(client);

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = INADDR_ANY;

    bind(sock, (struct sockaddr *)&server, sizeof(server));
    printf("UDP Server listening on port %d...\n", PORT);

    recvfrom(sock, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&client, &len);
    printf("UDP Received: %s\n", buffer);
    sendto(sock, "Hello from UDP server!", 23, 0, (struct sockaddr *)&client, len);
    close(sock);
}

// UDP CLIENT
void run_udp_client() {
    int sock;
    struct sockaddr_in server;
    char buffer[BUFFER_SIZE] = "Hello from UDP client!";
    socklen_t len = sizeof(server);

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &server.sin_addr);

    sendto(sock, buffer, strlen(buffer), 0, (struct sockaddr *)&server, len);
    recvfrom(sock, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&server, &len);
    printf("UDP Server replied: %s\n", buffer);
    close(sock);
}
