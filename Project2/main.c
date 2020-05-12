#include <windows.h>
#include <stdio.h>
#include<string.h>
#include<tlhelp32.h>
int Find(HANDLE CONST hStdOut,char* s) {
    int k;
    PROCESSENTRY32 peProcessEntry;
    TCHAR szBuff[1024];
    DWORD dwTemp;
    HANDLE CONST hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (INVALID_HANDLE_VALUE == hSnapshot) {
        return;
    }

    peProcessEntry.dwSize = sizeof(PROCESSENTRY32);
    Process32First(hSnapshot, &peProcessEntry);
    int c = 0;
    do {
        k = 1;
        for (int i = 0; i < strlen(s); i++) {
            if ((char)peProcessEntry.szExeFile[i] != s[i]) {
                k = 0;
                break;
            }
        }
            if (k == 1) {
                c++;
        }
    
    } while (Process32Next(hSnapshot, &peProcessEntry));
    CloseHandle(hSnapshot);
    return c;
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
    if (Find(hStdOut, s) <= 1) {
        printf("At's good\n");
    }
    else
        printf("O'h shit, i'm sorry\n");
    system("pause");
	return 0;
}