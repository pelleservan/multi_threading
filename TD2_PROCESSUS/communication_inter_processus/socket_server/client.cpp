#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main() {
    // Création du socket
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        std::cerr << "Erreur lors de la création du socket client." << std::endl;
        return -1;
    }

    // Configuration de l'adresse du serveur
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(8080); // Port du serveur

    // Connexion au serveur
    if (connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
        std::cerr << "Erreur lors de la connexion au serveur." << std::endl;
        close(clientSocket);
        return -1;
    }

    std::cout << "Connexion au serveur réussie." << std::endl;

    // Réception des données du serveur
    char buffer[1024] = {0};
    recv(clientSocket, buffer, sizeof(buffer), 0);

    std::cout << "Message du serveur : " << buffer << std::endl;

    // Fermeture du socket
    close(clientSocket);

    return 0;
}
