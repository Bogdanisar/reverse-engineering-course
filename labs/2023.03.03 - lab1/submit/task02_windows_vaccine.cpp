#include <stdio.h>
#include <Windows.h>


int main() {
    const char * const malwareMutexName = "WEBLAUNCHASSIST_MUTEX";
    HANDLE mutexHandle = CreateMutexA(NULL, TRUE, malwareMutexName);

    if (mutexHandle == NULL) {
        printf("CreateMutexA failed. Last error: %i\n", (int)GetLastError());
        return -1;
    }

    printf("Mutex %s is created\n", malwareMutexName); fflush(stdout);

    if (GetLastError() == ERROR_ALREADY_EXISTS) {
        printf("Mutex %s already exists\n", malwareMutexName); fflush(stdout);
        CloseHandle(mutexHandle);
        return 0;
    }

    printf("New mutex. Sleeping...\n"); fflush(stdout);
    while (1) {
        Sleep(2 * 1000);
    }

    return 0;
}
