#include <iostream>
#include <windows.h>

int main()
{
    DWORD pid = GetCurrentProcessId();
    std::cout << "Child process " << pid << " is running..." << std::endl;

    while (true) {
        std::cout << "Child process " << pid << " is still running..." << std::endl;
        Sleep(1000);
    }

    return 0;
}