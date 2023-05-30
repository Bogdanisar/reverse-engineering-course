#include <algorithm>
#include <cassert>
#include <cstring>
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


vector<pair<tstring, int>> windowTitleList;

BOOL CALLBACK GetWindowTitles(HWND hwnd, LPARAM lParam) {
    TCHAR windowTitle[1000];    
    int windowTitleLength = GetWindowText(hwnd, windowTitle, 1000);

    if (windowTitleLength == 0) {
        return TRUE;
    }

    DWORD pid;
    DWORD tid = GetWindowThreadProcessId(hwnd, &pid);
    assert(tid != 0);
    
    windowTitleList.push_back({windowTitle, (int)pid});

    return TRUE;
}

int main() {
    BOOL enumWindowsRet = EnumWindows(GetWindowTitles, 0);
    assert(enumWindowsRet != 0);

    sort(windowTitleList.begin(), windowTitleList.end());
    for (const auto& pair : windowTitleList) {      
        const tstring& title = pair.first; 
        int pid = pair.second;
        _tprintf(TEXT("pid = %5i; windowTitle = %s [%i]"), (int)pid, title.c_str(), (int)title.length());
      
        tstring targetTitle = TEXT("Minesweeper");
        if (title == targetTitle) {
            printf("  <----------------------------------------------  Here");
        }

        printf("\n");
    }

    printf("Enter any input to stop...\n");
    // getchar();

    return 0;
}
