#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main() {
    // Création du socket
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        std::cerr << "Erreur lors de la création du socket serveur." << std::endl;
        return -1;
    }

    // Configuration de l'adresse du serveur
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(8080); // Port du serveur

    // Liaison du socket à l'adresse et au port
    if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
        std::cerr << "Erreur lors de la liaison du socket à l'adresse." << std::endl;
        close(serverSocket);
        return -1;
    }

    // Attente de connexions
    if (listen(serverSocket, 10) == -1) {
        std::cerr << "Erreur lors de l'attente de connexions." << std::endl;
        close(serverSocket);
        return -1;
    }

    std::cout << "Le serveur écoute sur le port 8080..." << std::endl;

    // Acceptation d'une connexion
    int clientSocket = accept(serverSocket, nullptr, nullptr);
    if (clientSocket == -1) {
        std::cerr << "Erreur lors de l'acceptation de la connexion." << std::endl;
        close(serverSocket);
        return -1;
    }

    std::cout << "Connexion établie avec le client." << std::endl;

    // Envoi de données au client
    const char* message = "Bonjour, client !";
    send(clientSocket, message, strlen(message), 0);

    // Fermeture des sockets
    close(clientSocket);
    close(serverSocket);

    return 0;
}
