#include <windows.h>
#include <stdio.h>
#include<string.h>
#include<tlhelp32.h>
DWORD Find(HANDLE CONST hStdOut,char* s) {
    PROCESSENTRY32 peProcessEntry;
    TCHAR szBuff[1024];
    DWORD dwTemp;
    HANDLE CONST hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (INVALID_HANDLE_VALUE == hSnapshot) {
        return;
    }
    peProcessEntry.dwSize = sizeof(PROCESSENTRY32);
    Process32First(hSnapshot, &peProcessEntry);
    int c;
    do {
        c = 1;
        for (int i = 0; i < strlen(s); i++) {
            if ((char)peProcessEntry.szExeFile[i] != s[i]) {
                c = 0;
                break;
            } 
        } 
        if (c == 1) {
            return peProcessEntry.th32ParentProcessID;
        }
    } while (Process32Next(hSnapshot, &peProcessEntry));
    CloseHandle(hSnapshot);
    return 0;
}
int FindCount(HANDLE CONST hStdOut, char* s) {
    DWORD Found = Find(hStdOut, s);
    int k = 0;
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
        if (peProcessEntry.th32ParentProcessID == Found) k++;
    
    } while (Process32Next(hSnapshot, &peProcessEntry));
    CloseHandle(hSnapshot);
    return k;
}
int main(int argc, char* argv[]) {
    int c = 0;
    for (int i = 0; i < strlen(argv[0]); i++) {
        if (argv[0][i] == 92){
            c++;
        }
    }
    int j = 0;
    while (1) {
        if (argv[0][j] == 92) c--;
        j++;
        if (c == 0) break;
    }
    char* s = malloc((strlen(argv[0]) - j) * sizeof(char));
    for (int k = j; k < strlen(argv[0])+1; k++) {
        s[k - j] = argv[0][k];
    }
    HANDLE CONST hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (FindCount(hStdOut, s) <= 13) {
        printf("At's good\n");
    }
    else
        printf("O'h shit, i'm sorry\n");
    system("pause");
	return 0;
}
