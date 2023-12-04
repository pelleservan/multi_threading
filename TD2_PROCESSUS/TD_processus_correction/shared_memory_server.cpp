#include <iostream>
#include <windows.h>
#include <string>

#define SHARED_MEM_NAME L"C:\Users\Admin\Desktop\SEGULA_CM\my_shared_mem"
#define MUTEX_NAME L"C:\Users\Admin\Desktop\SEGULA_CM\my_shared_mutex"


int main() {
    HANDLE hMapFile = CreateFileMapping(
        INVALID_HANDLE_VALUE,    // Use the page file
        NULL,                    // Default security attributes
        PAGE_READWRITE,          // Allow read/write access to the shared memory
        0,                       // High-order 32 bits of the file size
        256,                     // Low-order 32 bits of the file size (in bytes)
        SHARED_MEM_NAME); // Name of the shared memory

    HANDLE hMutex = CreateMutex(NULL, FALSE, MUTEX_NAME);
    if (hMutex == NULL) {
        std::cerr << "Failed to create mutex. Error code: " << GetLastError() << std::endl;
        return 1;
    }

    if (hMapFile == NULL) {
        std::cerr << "Failed to create file mapping object. Error code: " << GetLastError() << std::endl;
        CloseHandle(hMutex);
        return 1;
    }

    LPCTSTR pBuf = (LPTSTR)MapViewOfFile(
        hMapFile,         // Handle to the mapping object
        FILE_MAP_ALL_ACCESS, // Read/write access
        0,  // High-order 32 bits of the starting offset
        0,  // Low-order 32 bits of the starting offset
        256); // Number of bytes to map

    if (pBuf == NULL) {
        std::cerr << "Failed to map view of file. Error code: " << GetLastError() << std::endl;
        CloseHandle(hMapFile);
        CloseHandle(hMutex);
        return 1;
    }

    while (1)
    {
        WaitForSingleObject(hMutex, INFINITE);

        std::cout << "Enter a message to send: ";
        std::string message;
        std::getline(std::cin, message);

        // Write the message to shared memory
        std::memcpy((void*)pBuf, message.c_str(), message.size());

        ReleaseMutex(hMutex);
    }

    // Unmap the shared memory
    UnmapViewOfFile(pBuf);


    // Close the file mapping object
    CloseHandle(hMapFile);

    CloseHandle(hMutex);

    return 0;
}