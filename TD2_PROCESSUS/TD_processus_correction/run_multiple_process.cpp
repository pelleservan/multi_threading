#include <windows.h>
#include <stdio.h>
#include <tchar.h>

#include <iostream>

#define WINDOWS_LEAN_AND_MEAN


int main(int argc, char** argv)
{
    PROCESS_INFORMATION processInfo;
    STARTUPINFOA si;
    bool ret = false;
    char  cmdLine[] = "C:\\Users\\x\\x\\x\\VERIF\\x64\\Debug\\child.exe";

    for (int i = 0; i < 5; i++)
    {
        ZeroMemory(&si, sizeof(STARTUPINFO));
        si.cb = sizeof(STARTUPINFO);
        ret = CreateProcessA(NULL, cmdLine, NULL, NULL, false, 0, NULL, NULL, &si,
            &processInfo);

        if (!ret)
        {
            std::cout << "Error CreateProcess" << std::endl;
            return EXIT_FAILURE;
        }

        std::cout << "Launched" << std::endl;
        Sleep(5000);

    }

    WaitForSingleObject(processInfo.hProcess, INFINITE);
    CloseHandle(processInfo.hProcess);
    CloseHandle(processInfo.hThread);

    std::cout << "Program exit" << std::endl;
    return EXIT_SUCCESS;

}