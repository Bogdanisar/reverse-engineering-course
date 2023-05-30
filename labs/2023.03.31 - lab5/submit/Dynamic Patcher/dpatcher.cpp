#include <algorithm>
#include <cassert>
#include <cstring>
#include <string.h>
#include <iostream>
#include <tchar.h>
#include <vector>
#include <windows.h>
#include <winuser.h>

using namespace std;

#ifndef UNICODE
    typedef std::string tstring;
#else
    typedef std::wstring tstring;
#endif

#define pv(x) std::cout<<#x<<" = "<<(x)<<"; ";std::cout.flush()
#define pn std::cout<<std::endl


enum GameCellType {
    GameCellType_Safe_Hidden_Question   = 0x0D,
    GameCellType_Safe_Hidden_Flag       = 0x0E,
    GameCellType_Safe_Hidden            = 0x0F,
    GameCellType_Border                 = 0x10,
    GameCellType_Safe_Visible_Empty     = 0x40,
    GameCellType_Safe_Visible_Digit1    = 0x41,
    GameCellType_Safe_Visible_Digit2    = 0x42,
    GameCellType_Safe_Visible_Digit3    = 0x43,
    GameCellType_Safe_Visible_Digit4    = 0x44,
    GameCellType_Safe_Visible_Digit5    = 0x45,
    GameCellType_Safe_Visible_Digit6    = 0x46,
    GameCellType_Safe_Visible_Digit7    = 0x47,
    GameCellType_Safe_Visible_Digit8    = 0x48,
    GameCellType_Bomb_Base              = 0x80,
    GameCellType_Bomb_Visible_OK        = 0x8A,
    GameCellType_Bomb_Hidden_Question   = 0x8D,
    GameCellType_Bomb_Hidden_Flag       = 0x8E,
    GameCellType_Bomb_Hidden            = 0x8F,
    GameCellType_Bomb_Visible_Exploded  = 0x0CC,
};


/* These map to the location inside the virtual memory of Minesweeper (which seems to be the same always) */
const int gameMatrixAddress = 0x01005340;
const int numberOfLinesAddress = 0x010056A8;
const int numberOfColumnsAddress = 0x010056AC;
const int maxLines = 27, maxColumns = 32;

HANDLE pHandle, tHandle;
unsigned char gameMatrix[maxLines][maxColumns] = {};
int numberOfLines, numberOfColumns;


//////////////// I ran this code in Windows 11 under Mingw64 ////////////////
//////////////// $> g++ dpatcher.cpp -o dpatcher.exe ////////////////

BOOL patchHighScore() {
    SIZE_T bytesTransfered;
    BOOL boolReturn;


    ////////////////////// Set seconds to 0 //////////////////////
    const int beginnerHighScoreSecondsAddress = 0x010056CC;
    const int intermediateHighScoreSecondsAddress = 0x010056D0;
    const int expertHighScoreSecondsAddress = 0x010056D4;
    DWORD highscore = 0;

    bytesTransfered = 0;
    boolReturn = WriteProcessMemory(pHandle, (PVOID)beginnerHighScoreSecondsAddress, &highscore, sizeof(highscore), &bytesTransfered);
    if (boolReturn == 0) {
        printf("Line %4i: WriteProcessMemory() failed! Last error: %u\n", (int)__LINE__, (unsigned)GetLastError());
        return FALSE;
    }

    bytesTransfered = 0;
    boolReturn = WriteProcessMemory(pHandle, (PVOID)intermediateHighScoreSecondsAddress, &highscore, sizeof(highscore), &bytesTransfered);
    if (boolReturn == 0) {
        printf("Line %4i: WriteProcessMemory() failed! Last error: %u\n", (int)__LINE__, (unsigned)GetLastError());
        return FALSE;
    }

    bytesTransfered = 0;
    boolReturn = WriteProcessMemory(pHandle, (PVOID)expertHighScoreSecondsAddress, &highscore, sizeof(highscore), &bytesTransfered);
    if (boolReturn == 0) {
        printf("Line %4i: WriteProcessMemory() failed! Last error: %u\n", (int)__LINE__, (unsigned)GetLastError());
        return FALSE;
    }
    ////////////////////// Set seconds to 0 //////////////////////


    ////////////////////// Set name to "Burcea-Bogdan" //////////////////////
    const int beginnerHighScoreNameAddress = 0x010056D8;
    const int intermediateHighScoreNameAddress = 0x01005718;
    const int expertHighScoreNameAddress = 0x01005758;
    WCHAR name[] = L"Burcea-Bogdan";

    bytesTransfered = 0;
    boolReturn = WriteProcessMemory(pHandle, (PVOID)beginnerHighScoreNameAddress, &name, sizeof(name), &bytesTransfered);
    if (boolReturn == 0) {
        printf("Line %4i: WriteProcessMemory() failed! Last error: %u\n", (int)__LINE__, (unsigned)GetLastError());
        return FALSE;
    }

    bytesTransfered = 0;
    boolReturn = WriteProcessMemory(pHandle, (PVOID)intermediateHighScoreNameAddress, &name, sizeof(name), &bytesTransfered);
    if (boolReturn == 0) {
        printf("Line %4i: WriteProcessMemory() failed! Last error: %u\n", (int)__LINE__, (unsigned)GetLastError());
        return FALSE;
    }

    bytesTransfered = 0;
    boolReturn = WriteProcessMemory(pHandle, (PVOID)expertHighScoreNameAddress, &name, sizeof(name), &bytesTransfered);
    if (boolReturn == 0) {
        printf("Line %4i: WriteProcessMemory() failed! Last error: %u\n", (int)__LINE__, (unsigned)GetLastError());
        return FALSE;
    }
    ////////////////////// Set name to "Burcea-Bogdan" //////////////////////


    return TRUE;
}

/* Ignore */
void printAllocationInfoForAddress(long long address) {
    MEMORY_BASIC_INFORMATION mbi;
    int readBytes = VirtualQueryEx(pHandle, (LPCVOID)address, &mbi, sizeof(mbi));
    assert(readBytes == sizeof(mbi));

    pv(mbi.BaseAddress); pn;
    pv(mbi.AllocationBase); pn;
    pv(mbi.AllocationProtect); pn;
    pv(mbi.RegionSize); pn;
    pv(mbi.Protect); pn;
    pn;
}

/* This patches the string resource inside the .rsrc segment */
BOOL patchCreatorName() {
    SIZE_T bytesTransfered;
    BOOL boolReturn;
    const int creatorNameAddress = 0x101F118;

    WCHAR oldName[1000] = {};
    bytesTransfered = 0;
    boolReturn = ReadProcessMemory(pHandle, (PVOID)creatorNameAddress, oldName, sizeof(oldName), &bytesTransfered);
    if (boolReturn == 0) {
        printf("Line %4i: WriteProcessMemory() failed! Last error: %u\n", (int)__LINE__, (unsigned)GetLastError());
        return FALSE;
    }
    printf("Old creator name: \"%ls\"\n", oldName); // "by Robert Donner and Curt Johnson"

    // printAllocationInfoForAddress(creatorNameAddress);

    WCHAR myName[] = L"by Burcea Bogdan-Madalin";
    DWORD oldProtect;
    boolReturn = VirtualProtectEx(pHandle, (PVOID)creatorNameAddress, sizeof(myName), PAGE_READWRITE, &oldProtect);
    if (boolReturn == 0) {
        printf("Line %4i: VirtualProtectEx() failed! Last error: %u\n", (int)__LINE__, (unsigned)GetLastError());
        return FALSE;
    }

    bytesTransfered = 0;
    boolReturn = WriteProcessMemory(pHandle, (PVOID)creatorNameAddress, myName, sizeof(myName), &bytesTransfered);
    if (boolReturn == 0) {
        printf("Line %4i: WriteProcessMemory() failed! Last error: %u\n", (int)__LINE__, (unsigned)GetLastError());
        return FALSE;
    }

    return TRUE;
}

BOOL readMatrixLines() {
    SIZE_T bytesTransfered;
    BOOL boolReturn;

    bytesTransfered = 0;
    boolReturn = ReadProcessMemory(pHandle, (LPCVOID)numberOfLinesAddress, &numberOfLines, sizeof(numberOfLines), &bytesTransfered);
    if (boolReturn == 0) {
        printf("Line %4i: ReadProcessMemory() failed! Last error: %u\n", (int)__LINE__, (unsigned)GetLastError());
        return FALSE;
    }

    bytesTransfered = 0;
    boolReturn = ReadProcessMemory(pHandle, (LPCVOID)numberOfColumnsAddress, &numberOfColumns, sizeof(numberOfColumns), &bytesTransfered);
    if (boolReturn == 0) {
        printf("Line %4i: ReadProcessMemory() failed! Last error: %u\n", (int)__LINE__, (unsigned)GetLastError());
        return FALSE;
    }

    return TRUE;
}

BOOL readGameMatrix() {
    SIZE_T bytesTransfered;
    BOOL boolReturn;

    bytesTransfered = 0;
    boolReturn = ReadProcessMemory(pHandle, (LPCVOID)gameMatrixAddress, gameMatrix, sizeof(gameMatrix), &bytesTransfered);
    if (boolReturn == 0) {
        printf("Line %4i: ReadProcessMemory() failed! Last error: %u\n", (int)__LINE__, (unsigned)GetLastError());
        return FALSE;
    }

    return TRUE;
}

void printGameMatrix() {
    for (int i = 0; i <= numberOfLines + 1; ++i) {
        for (int j = 0; j <= numberOfColumns + 1; ++j) {
            printf("%2hhX ", gameMatrix[i][j]);
        }
        printf("\n");
    }
}

void patchCellTypesInGameMatrix() {
    for (int i = 1; i <= numberOfLines; ++i) {
        for (int j = 1; j <= numberOfColumns; ++j) {
            if (gameMatrix[i][j] & GameCellType_Bomb_Base) { // Has a bomb
                gameMatrix[i][j] = GameCellType_Bomb_Hidden_Flag;
            }
            else if (gameMatrix[i][j] == GameCellType_Safe_Hidden ||
                     gameMatrix[i][j] == GameCellType_Safe_Hidden_Question ||
                     gameMatrix[i][j] == GameCellType_Safe_Hidden_Flag) {
                gameMatrix[i][j] = GameCellType_Safe_Hidden_Question;
            }
        }
    }

    // Now we need to remove the question mark from cells that have bombs around them.

    const int dx[8] = {-1, -1, -1,  0,  0, +1, +1, +1};
    const int dy[8] = {-1,  0, +1, -1, +1, -1,  0, +1};
    for (int i = 1; i <= numberOfLines; ++i) {
        for (int j = 1; j <= numberOfColumns; ++j) {
            if (gameMatrix[i][j] != GameCellType_Safe_Hidden_Question) {
                continue;
            }

            int bombsAround = 0;
            for (int k = 0; k < 8; ++k) {
                if (gameMatrix[i + dx[k]][j + dy[k]] & GameCellType_Bomb_Base) {
                    bombsAround += 1;
                }
            }

            if (bombsAround != 0) {
                gameMatrix[i][j] = GameCellType_Safe_Hidden;
            }
        }
    }
}

/**
 * This does work on its own, but the problem is that the GUI doesn't refresh after the cell data is updated.
 * In order to see the effects after updating just the gameMatrix memory, the following workaround could be used:
 * Press on the mouse left-click and hold it while dragging the mouse around on the game cells.
 * This will refresh the GUI information for the hovered cells.
*/
BOOL writeGameMatrix() {
    SIZE_T bytesTransfered;
    BOOL boolReturn;

    bytesTransfered = 0;
    boolReturn = WriteProcessMemory(pHandle, (PVOID)gameMatrixAddress, gameMatrix, sizeof(gameMatrix), &bytesTransfered);
    if (boolReturn == 0) {
        printf("Line %4i: WriteProcessMemory() failed! Last error: %u\n", (int)__LINE__, (unsigned)GetLastError());
        return FALSE;
    }

    return TRUE;
}

BOOL patchGameMatrix() {
    SIZE_T bytesTransfered;
    BOOL boolReturn;
    HANDLE remoteThreadHandle = NULL;
    unsigned long long remoteFunctionAddress;
    DWORD remoteTid;

    if (!readMatrixLines()) { return FALSE; }
    pv(numberOfLines); pn;
    pv(numberOfColumns); pn;

    if (!readGameMatrix()) { return FALSE; }
    printGameMatrix();
    patchCellTypesInGameMatrix(); pn; pn;
    printGameMatrix();
    if (!writeGameMatrix()) { return FALSE; }


    /* This is hacky as hell.
       CreateRemoteThread() is supposed to work on a procedure that expects an 8-byte pointer as a single argument.
       Sooo the API lets me send 8 bytes on the stack (probably) and my GUI-update subroutine expects a 4-byte int (with value = 4).
       Casting the value '4' as an 8-byte pointer and sending it as the argument seems to work ¯\_(ツ)_/¯.
    */
    // remoteFunctionAddress = 0x0100367A; /* startNewGame() */
    remoteFunctionAddress = 0x01001950; /* The function that updates the GUI at the end of startNewGame() */
    remoteThreadHandle = CreateRemoteThread(pHandle, NULL, 0, (LPTHREAD_START_ROUTINE)remoteFunctionAddress, (LPVOID)4 /*argument*/, 0 /*dwCreationFlags*/, &remoteTid);
    if (remoteThreadHandle == NULL) { return FALSE; }

    BOOL closeRet = CloseHandle(remoteThreadHandle);
    if (closeRet == FALSE) {
        printf("CloseHandle() failed! Last error: %u\n", (unsigned)GetLastError());
        return FALSE;
    }

    return TRUE;
}

BOOL patchUnflaggedBombsNumber() {
    SIZE_T bytesTransfered;
    BOOL boolReturn;
    const unsigned long long unflaggedBombsNumberAddress = 0x01005194;
    DWORD newUnflaggedBombsNumber = 0;
    DWORD remoteThreadID;

    // Update the number in-memory

    bytesTransfered = 0;
    boolReturn = WriteProcessMemory(pHandle, (LPVOID)unflaggedBombsNumberAddress, &newUnflaggedBombsNumber, sizeof(newUnflaggedBombsNumber), &bytesTransfered);
    if (boolReturn == 0) {
        printf("Line %4i: WriteProcessMemory() failed! Last error: %u\n", (int)__LINE__, (unsigned)GetLastError());
        return FALSE;
    }

    // Update the top-left counter in the GUI. Thankfully, there's a subroutine inside Minesweeper that does this.

    const unsigned long long remoteFunctionAddress = 0x01002801; /* Function that updates the flag number (in-memory and in-GUI) */
    HANDLE remoteThreadHandle = CreateRemoteThread(pHandle,
                                                   NULL, /*Security attributes. Use default*/
                                                   0, /*Stack size. Use default*/
                                                   (LPTHREAD_START_ROUTINE)remoteFunctionAddress,
                                                   (LPVOID)0, /*Argument. Our procedure doesn't have any.*/
                                                   0, /*dwCreationFlags*/
                                                   &remoteThreadID);
    if (remoteThreadHandle == NULL) {
        printf("Line %4i: CreateRemoteThread() failed! Last error: %u\n", (int)__LINE__, (unsigned)GetLastError());
        return FALSE;
    }

    BOOL closeRet = CloseHandle(remoteThreadHandle);
    if (closeRet == FALSE) {
        printf("CloseHandle() failed! Last error: %u\n", (unsigned)GetLastError());
        return FALSE;
    }

    return TRUE;
}

BOOL patchInstruction(const unsigned long long instructionAddress, const unsigned char instructionBytes[], const int numInstructionBytes) {
    SIZE_T bytesTransfered;
    BOOL boolReturn;
    DWORD oldProtect;
    unsigned char instructionBuffer[100];
    const int numShowInstructionBytes = 0; /* DEBUG */

    bytesTransfered = 0;
    boolReturn = ReadProcessMemory(pHandle, (LPCVOID)instructionAddress, instructionBuffer, sizeof(instructionBuffer), &bytesTransfered);
    if (boolReturn == 0) {
        printf("Line %4i: ReadProcessMemory() failed! Last error: %u\n", (int)__LINE__, (unsigned)GetLastError());
        return FALSE;
    }
    // printf("Old instruction: %2hhX %2hhX %2hhX\n", instructionBuffer[0], instructionBuffer[1], instructionBuffer[2]);
    for (int i = 0; i < numShowInstructionBytes; ++i) { printf("instructionBuffer[%2i] = %2hhX\n", i, instructionBuffer[i]); }


    boolReturn = VirtualProtectEx(pHandle, (PVOID)instructionAddress, numInstructionBytes, PAGE_EXECUTE_READWRITE, &oldProtect);
    if (boolReturn == 0) {
        printf("Line %4i: VirtualProtectEx() failed! Last error: %u\n", (int)__LINE__, (unsigned)GetLastError());
        return FALSE;
    }
    // pv(oldProtect); pn;


    bytesTransfered = 0;
    boolReturn = WriteProcessMemory(pHandle, (PVOID)instructionAddress, instructionBytes, numInstructionBytes, &bytesTransfered);
    if (boolReturn == 0) {
        printf("Line %4i: WriteProcessMemory() failed! Last error: %u\n", (int)__LINE__, (unsigned)GetLastError());
        return FALSE;
    }

    boolReturn = FlushInstructionCache(pHandle, NULL, 0 /*Whatever*/);
    assert(boolReturn != FALSE);

    boolReturn = VirtualProtectEx(pHandle, (PVOID)instructionAddress, numInstructionBytes, PAGE_EXECUTE_READ, &oldProtect);
    if (boolReturn == 0) {
        printf("Line %4i: VirtualProtectEx() failed! Last error: %u\n", (int)__LINE__, (unsigned)GetLastError());
        return FALSE;
    }
    // pv(oldProtect); pn;


    bytesTransfered = 0;
    boolReturn = ReadProcessMemory(pHandle, (LPCVOID)instructionAddress, instructionBuffer, sizeof(instructionBuffer), &bytesTransfered);
    if (boolReturn == 0) {
        printf("Line %4i: ReadProcessMemory() failed! Last error: %u\n", (int)__LINE__, (unsigned)GetLastError());
        return FALSE;
    }
    for (int i = 0; i < numShowInstructionBytes; ++i) { printf("instructionBuffer[%2i] = %2hhX\n", i, instructionBuffer[i]); }


    return TRUE;
}

BOOL patchNewGameInstructions() {
    const unsigned int setBombTypeInstructionAddress = 0x010036FA; // inside startNewGame()
    const unsigned char patchedBombInstruction[3] = {
        (unsigned char)'\xC6', (unsigned char)'\x00', (unsigned char)'\x8E'
    }; // mov     byte ptr [eax], 8Eh

    const unsigned int initCellTypeInstructionAddress = 0x01002EDB; // inside initGameCellsWithEmptyCellsAndBorder()
    const unsigned char patchedInitCellInstruction[7] = {
        (unsigned char)'\xC6', (unsigned char)'\x80', (unsigned char)'\x40', (unsigned char)'\x53',
        (unsigned char)'\x00', (unsigned char)'\x01', (unsigned char)'\x0D'
    }; // mov     gameCellMatrix[eax], 0Dh

    // When a new game is started, all bombs will be flagged.
    if (!patchInstruction(setBombTypeInstructionAddress, patchedBombInstruction, sizeof(patchedBombInstruction))) {
        return FALSE;
    }

    // When a new game is started, all non-bombs will be question-marks.
    if (!patchInstruction(initCellTypeInstructionAddress, patchedInitCellInstruction, sizeof(patchedInitCellInstruction))) {
        return FALSE;
    }

    return TRUE;
}


void ProcessMinesweeperPid(int pid) {
    printf("Minesweeper pid = %i\n", pid);

    pHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
    if (pHandle == NULL) {
        printf("OpenProcess() failed! Last erorr: %u\n", (unsigned)GetLastError());
        return;
    }

    if (!patchHighScore()) { goto end; }
    if (!patchCreatorName()) { goto end; }
    if (!patchGameMatrix()) { goto end; }
    if (!patchUnflaggedBombsNumber()) { goto end; }
    if (!patchNewGameInstructions()) { goto end; }

end:
    if (pHandle != NULL) {
        BOOL closeRet = CloseHandle(pHandle);
        if (closeRet == FALSE) {
            printf("CloseHandle() failed! Last error: %u\n", (unsigned)GetLastError());
        }

        pHandle = NULL;
    }
}

void Nope() {
    // boolReturn = DebugActiveProcess(pid);
    // assert(boolReturn != FALSE);

    // DEBUG_EVENT debug_event;
    // boolReturn = WaitForDebugEvent(&debug_event, INFINITE);
    // assert(boolReturn != FALSE);


    // // Process should be stopped now. Move EIP
    // tHandle = OpenThread(THREAD_ALL_ACCESS, FALSE, debug_event.dwThreadId);
    // assert(tHandle != NULL);

    // CONTEXT threadContext;
    // boolReturn = GetThreadContext(tHandle, &threadContext);
    // assert(boolReturn != FALSE);

    // pv(threadContext.Rip); pn;
    // threadContext.Rbx = 4;
    // threadContext.Rip = 0x01003745;


    // // Release the process.
    // boolReturn = ContinueDebugEvent(debug_event.dwProcessId,
    //                                 debug_event.dwThreadId,
    //                                 DBG_CONTINUE);
    // assert(boolReturn != FALSE);

    // boolReturn = DebugActiveProcessStop(pid);
    // assert(boolReturn != FALSE);
}

BOOL CALLBACK GetWindowTitles(HWND hwnd, LPARAM lParam) {
    static tstring targetTitle = TEXT("Minesweeper");

    TCHAR windowTitle[100];
    int windowTitleLength = GetWindowText(hwnd, windowTitle, 100);

    if (windowTitleLength != 0 && targetTitle == tstring(windowTitle)) {
        DWORD pid;
        DWORD tid = GetWindowThreadProcessId(hwnd, &pid);
        assert(tid != 0);

        ProcessMinesweeperPid((int)pid);
    }

    return TRUE;
}

int main() {
    BOOL enumWindowsRet = EnumWindows(GetWindowTitles, 0);
    assert(enumWindowsRet != 0);

    printf("Enter any input to stop...\n");
    // getchar();

    return 0;
}
