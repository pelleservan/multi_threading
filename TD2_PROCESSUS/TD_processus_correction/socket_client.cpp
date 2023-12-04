#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")
#define _WINSOCK_DEPRECATED_NO_WARNINGS

int main()
{
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed." << std::endl;
        return 1;
    }

    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Failed to create socket." << std::endl;
        return 1;
    }

    sockaddr_in addr;
    addr.sin_family = AF_INET;
    //addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);
    addr.sin_port = htons(1234);

    if (connect(clientSocket, (SOCKADDR*)&addr, sizeof(addr)) == SOCKET_ERROR) {
        std::cerr << "Failed to connect to server." << std::endl;
        closesocket(clientSocket);
        return 1;
    }

    std::cout << "Connected to server." << std::endl;

    char buffer[1024];
    int numBytes = 0;

    while (true) {
        std::cout << "Enter message to send: ";
        std::cin.getline(buffer, sizeof(buffer));

        if (strlen(buffer) == 0) {
            std::cout << "Empty message. Closing connection." << std::endl;
            break;
        }

        if (send(clientSocket, buffer, strlen(buffer), 0) == SOCKET_ERROR) {
            std::cerr << "Failed to send data to server." << std::endl;
            closesocket(clientSocket);
            break;
        }

        numBytes = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (numBytes <= 0) {
            std::cout << "Server disconnected." << std::endl;
            break;
        }

        std::cout << "Received " << numBytes << " bytes: " << buffer << std::endl;
    }

    closesocket(clientSocket);

    WSACleanup();

    return 0;
}