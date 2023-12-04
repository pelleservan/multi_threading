#include <iostream>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

int main()
{
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed." << std::endl;
        return 1;
    }

    SOCKET listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listenSocket == INVALID_SOCKET) {
        std::cerr << "Failed to create socket." << std::endl;
        return 1;
    }

    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(1234);

    if (bind(listenSocket, (SOCKADDR*)&addr, sizeof(addr)) == SOCKET_ERROR) {
        std::cerr << "Failed to bind socket." << std::endl;
        closesocket(listenSocket);
        return 1;
    }

    if (listen(listenSocket, SOMAXCONN) == SOCKET_ERROR) {
        std::cerr << "Failed to listen on socket." << std::endl;
        closesocket(listenSocket);
        return 1;
    }

    std::cout << "Listening on port 1234..." << std::endl;

    SOCKET clientSocket = accept(listenSocket, NULL, NULL);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Failed to accept client connection." << std::endl;
        closesocket(listenSocket);
        return 1;
    }

    std::cout << "Client connected." << std::endl;

    char buffer[1024];
    int numBytes = 0;

    while (true) {
        numBytes = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (numBytes <= 0) {
            std::cout << "Client disconnected." << std::endl;
            break;
        }

        std::cout << "Received " << numBytes << " bytes: " << buffer << std::endl;

        if (send(clientSocket, buffer, numBytes, 0) == SOCKET_ERROR) {
            std::cerr << "Failed to send data to client." << std::endl;
            closesocket(clientSocket);
            break;
        }
    }

    closesocket(clientSocket);
    closesocket(listenSocket);

    WSACleanup();

    return 0;
}
