#include <iostream>
#include <windows.h>

#define SHARED_MEM_NAME L"C:\Users\Admin\Desktop\SEGULA_CM\my_shared_mem"
#define MUTEX_NAME L"C:\Users\Admin\Desktop\SEGULA_CM\my_shared_mutex"

int main() {
    HANDLE hMapFile = OpenFileMapping(
        FILE_MAP_ALL_ACCESS, // Read/write access
        FALSE,               // Do not inherit the name
        SHARED_MEM_NAME); // Name of the shared memory

    if (hMapFile == NULL) {
        std::cerr << "Failed to open file mapping object. Error code: " << GetLastError() << std::endl;
        return 1;
    }

    HANDLE hMutex = OpenMutex(MUTEX_ALL_ACCESS, FALSE, MUTEX_NAME);
    if (hMutex == NULL) {
        std::cerr << "Failed to open mutex. Error code: " << GetLastError() << std::endl;
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
        return 1;
    }
    while (1)
    {
        WaitForSingleObject(hMutex, INFINITE);

        // Read the message from shared memory
        std::string message((char*)pBuf);

        std::cout << "Message received: " << message << std::endl;

        ReleaseMutex(hMutex);
    }

    // Unmap the shared memory
    UnmapViewOfFile(pBuf);

    // Close the file mapping object
    CloseHandle(hMapFile);

    CloseHandle(hMutex);

    return 0;
}
