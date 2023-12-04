#include <iostream>
#include <sys/sysctl.h>
#include <cstring>

int main() {
    // Définir la structure pour stocker les informations sur les processus
    struct kinfo_proc* processes;
    
    // Obtenir le nombre de processus actifs
    int processCount;
    size_t structSize = 0;
    int mib[4] = { CTL_KERN, KERN_PROC, KERN_PROC_ALL, 0 };
    
    if (sysctl(mib, 4, NULL, &structSize, NULL, 0) < 0) {
        std::cerr << "Erreur lors de l'obtention de la taille de la structure kinfo_proc." << std::endl;
        return 1;
    }
    
    processCount = static_cast<int>(structSize / sizeof(struct kinfo_proc));
    
    // Allouer de la mémoire pour stocker les informations sur les processus
    processes = new struct kinfo_proc[processCount];
    
    // Obtenir la liste des processus actifs
    if (sysctl(mib, 4, processes, &structSize, NULL, 0) < 0) {
        std::cerr << "Erreur lors de l'obtention de la liste des processus." << std::endl;
        delete[] processes;
        return 1;
    }
    
    // Afficher les informations sur chaque processus
    std::cout << "Liste des processus actifs :" << std::endl;
    for (int i = 0; i < processCount; ++i) {
        std::cout << "PID : " << processes[i].kp_proc.p_pid
                  << ", Nom : " << processes[i].kp_proc.p_comm << std::endl;
    }
    
    // Libérer la mémoire allouée
    delete[] processes;
    
    return 0;
}
