#include <iostream>
#include <windows.h>
#include <string>

int main()
{
    HANDLE hMailslot = CreateMailslotA("\\\\.\\mailslot\\my_mailslot", 0, MAILSLOT_WAIT_FOREVER, NULL);
    if (hMailslot == INVALID_HANDLE_VALUE) {
        std::cerr << "Failed to create mailslot. Error code: " << GetLastError() << std::endl;
        return 1;
    }

    while (1)
    {
        char buffer[256];
        DWORD bytesRead, messages;
        BOOL result = GetMailslotInfo(hMailslot, NULL, &bytesRead, &messages, NULL);
        if (!result) {
            std::cerr << "Failed to get mailslot info. Error code: " << GetLastError() << std::endl;
            CloseHandle(hMailslot);
            return 1;
        }

        if (bytesRead == MAILSLOT_NO_MESSAGE) {
            std::cout << "No message received." << std::endl;
        }
        else {
            result = ReadFile(hMailslot, buffer, sizeof(buffer) - 1, &bytesRead, NULL);
            if (!result) {
                std::cerr << "Failed to read message from mailslot. Error code: " << GetLastError() << std::endl;
                CloseHandle(hMailslot);
                return 1;
            }

            buffer[bytesRead] = '\0';
            std::cout << "Message received: " << buffer << std::endl;
        }
        Sleep(1000);
    }

    CloseHandle(hMailslot);

    return 0;
}