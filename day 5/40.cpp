#include <windows.h>
#include <stdio.h>

void displayPermissions(DWORD attributes) {
    printf("File Permissions: ");

    if (attributes & FILE_ATTRIBUTE_READONLY)
        printf("r");
    else
        printf("-");

    if (attributes & FILE_ATTRIBUTE_DIRECTORY)
        printf("d");
    else
        printf("-");

    printf("\n");
}

void displayUserInformation(LPCTSTR filename) {
    DWORD attributes = GetFileAttributes(filename);

    if (attributes == INVALID_FILE_ATTRIBUTES) {
        perror("Error getting file information");
        return;
    }

    displayPermissions(attributes);

    // Retrieving owner and group information on Windows is more involved and might require additional code.
    // This example focuses on basic file attributes.
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    LPCTSTR filename = argv[1];

    displayUserInformation(filename);

    return 0;
}

