#include <windows.h>
#include <stdio.h>
#include<tlhelp32.h>
VOID PrintProcessList(HANDLE CONST hStdOut) {
    PROCESSENTRY32 peProcessEntry;
    TCHAR szBuff[1024];
    DWORD dwTemp;
    HANDLE CONST hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (INVALID_HANDLE_VALUE == hSnapshot) {
        return;
    }

    peProcessEntry.dwSize = sizeof(PROCESSENTRY32);
    Process32First(hSnapshot, &peProcessEntry);
    do {
        wsprintf(szBuff, L"%s\n",peProcessEntry.szExeFile);
        WriteConsole(hStdOut, szBuff, lstrlen(szBuff), &dwTemp, NULL);
    } while (Process32Next(hSnapshot, &peProcessEntry));

    CloseHandle(hSnapshot);
}

int main() {
    HANDLE CONST hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    PrintProcessList(hStdOut);
    ExitProcess(0);
    system("pause");
    return 0;
}