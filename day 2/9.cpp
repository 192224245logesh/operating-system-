#include <stdio.h>
#include <windows.h>

#define SHM_SIZE 1024

// Structure to represent the shared data
typedef struct {
    int data;
} SharedData;

int main() {
    HANDLE hMapFile;
    LPCTSTR pBuf;

    // Create or open a file mapping object
    hMapFile = CreateFileMapping(
        INVALID_HANDLE_VALUE,   // Use the page file
        NULL,                   // Default security attributes
        PAGE_READWRITE,         // Read/write access
        0,                      // High-order DWORD of the maximum size of the file mapping object
        SHM_SIZE,               // Low-order DWORD of the maximum size of the file mapping object
        "Local\\MyFileMappingObject" // Name of the file mapping object
    );

    if (hMapFile == NULL) {
        fprintf(stderr, "Could not create file mapping object (%lu)\n", GetLastError());
        return 1;
    }

    // Map the view of the file mapping into the address space
    pBuf = (LPTSTR)MapViewOfFile(
        hMapFile,               // Handle to file mapping object
        FILE_MAP_ALL_ACCESS,    // Read/write access
        0,
        0,
        SHM_SIZE
    );

    if (pBuf == NULL) {
        fprintf(stderr, "Could not map view of file (%lu)\n", GetLastError());
        CloseHandle(hMapFile);
        return 1;
    }

    // Parent process writes to shared memory
    SharedData* sharedMemory = (SharedData*)pBuf;
    sharedMemory->data = 42;
    printf("Parent process wrote data: %d\n", sharedMemory->data);

    // Create a child process
    PROCESS_INFORMATION pi;
    STARTUPINFO si;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    if (CreateProcess(
        NULL,
        "child_process.exe", // Replace with the actual name of your child process executable
        NULL,
        NULL,
        FALSE,
        0,
        NULL,
        NULL,
        &si,
        &pi
    )) {
        // Wait for the child process to finish
        WaitForSingleObject(pi.hProcess, INFINITE);

        // Close process handle
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    } else {
        fprintf(stderr, "CreateProcess failed (%lu)\n", GetLastError());
    }

    // Unmap the file view and close the file mapping object
    UnmapViewOfFile(pBuf);
    CloseHandle(hMapFile);

    return 0;
}

