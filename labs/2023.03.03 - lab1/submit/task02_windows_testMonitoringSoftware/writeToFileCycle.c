#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

int main() {
    const char * const file = "writeToMeC.txt";
    while (1) {
        const int seconds = 3;
        printf("Sleeping for %i seconds\n", seconds); fflush(stdout);
        Sleep(seconds * 1000);

        printf("Writing to file: %s\n\n", file); fflush(stdout);
        FILE *fout = fopen(file, "w");
        fprintf(fout, "Hello\n");
        fclose(fout);
    }

    return 0;
}
