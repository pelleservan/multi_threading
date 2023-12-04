#include <iostream>
#include <windows.h>
#include <string>

int main()
{
    HANDLE hMailslot = CreateFileA("\\\\.\\mailslot\\my_mailslot", GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hMailslot == INVALID_HANDLE_VALUE) {
        std::cerr << "Failed to open mailslot. Error code: " << GetLastError() << std::endl;
        return 1;
    }

    while (1)
    {
        std::cout << "Enter a message to send: ";
        std::string message;
        std::getline(std::cin, message);

        DWORD bytesWritten;
        BOOL result = WriteFile(hMailslot, message.c_str(), message.size(), &bytesWritten, NULL);
        if (!result) {
            std::cerr << "Failed to write message to mailslot. Error code: " << GetLastError() << std::endl;
            CloseHandle(hMailslot);
            return 1;
        }

        std::cout << "Message sent successfully." << std::endl;

    }

    CloseHandle(hMailslot);

    return 0;
}