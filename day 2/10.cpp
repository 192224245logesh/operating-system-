#include <stdio.h>
#include <windows.h>

#define MESSAGE_BUFFER_SIZE 50

// Structure to represent the message
typedef struct {
    long messageType;
    char text[MESSAGE_BUFFER_SIZE];
} Message;

int main() {
    HANDLE hMapFile;
    Message* pBuf;

    // Create or open a file mapping object
    hMapFile = CreateFileMapping(
        INVALID_HANDLE_VALUE,   // Use the page file
        NULL,                   // Default security attributes
        PAGE_READWRITE,         // Read/write access
        0,                      // High-order DWORD of the maximum size of the file mapping object
        sizeof(Message),        // Low-order DWORD of the maximum size of the file mapping object
        "Local\\MyFileMappingObject" // Name of the file mapping object
    );

    if (hMapFile == NULL) {
        fprintf(stderr, "Could not create file mapping object (%lu)\n", GetLastError());
        return 1;
    }

    // Map the view of the file mapping into the address space
    pBuf = (Message*)MapViewOfFile(
        hMapFile,               // Handle to file mapping object
        FILE_MAP_ALL_ACCESS,    // Read/write access
        0,
        0,
        sizeof(Message)
    );

    if (pBuf == NULL) {
        fprintf(stderr, "Could not map view of file (%lu)\n", GetLastError());
        CloseHandle(hMapFile);
        return 1;
    }

    // Parent process sends a message to the queue
    printf("Parent process sending a message...\n");
    snprintf(pBuf->text, MESSAGE_BUFFER_SIZE, "Hello from parent!");

    printf("Parent process sent message: %s\n", pBuf->text);

    // Create a child process
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi)); // Fix: ZeroMemory instead of RtlZeroMemory

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

