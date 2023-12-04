#include <iostream>
#include <windows.h>
#include <tlhelp32.h>

void terminateProcess(DWORD processID)
{
    HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hProcessSnap == INVALID_HANDLE_VALUE) {
        return;
    }

    PROCESSENTRY32 pe32;
    pe32.dwSize = sizeof(PROCESSENTRY32);

    if (!Process32First(hProcessSnap, &pe32)) {
        CloseHandle(hProcessSnap);
        return;
    }

    do {
        if (pe32.th32ProcessID == processID) {
            HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, processID);
            if (hProcess != NULL) {
                TerminateProcess(hProcess, 0);
                CloseHandle(hProcess);
            }
            break;
        }
    } while (Process32Next(hProcessSnap, &pe32));

    CloseHandle(hProcessSnap);
}

int main()
{
    terminateProcess();
    std::cout << "Hello World!\n";
}
