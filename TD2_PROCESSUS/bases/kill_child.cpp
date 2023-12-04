#include <iostream>
#include <cstring>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    const char* targetProcessName = "child";

    // Utilisez la commande "pgrep" pour obtenir les PIDs des processus cibles
    std::string pgrepCommand = "pgrep " + std::string(targetProcessName);
    FILE* pgrepOutput = popen(pgrepCommand.c_str(), "r");

    if (!pgrepOutput) {
        std::cerr << "Erreur lors de l'exécution de la commande pgrep." << std::endl;
        return 1;
    }

    // Lire les PIDs depuis la sortie de pgrep
    char buffer[128];
    while (fgets(buffer, sizeof(buffer), pgrepOutput) != nullptr) {
        // Convertir le PID en entier
        int pid = std::stoi(buffer);

        // Envoyer le signal SIGTERM pour arrêter le processus
        if (kill(pid, SIGTERM) == 0) {
            std::cout << "Arrêt du processus avec PID : " << pid << std::endl;
        } else {
            std::cerr << "Erreur lors de l'arrêt du processus avec PID : " << pid << std::endl;
        }
    }

    // Fermer la sortie de pgrep
    pclose(pgrepOutput);

    // Attendre la fin de tous les processus fils
    int status;
    while (waitpid(-1, &status, WNOHANG) > 0) {}

    return 0;
}
