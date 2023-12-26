#include <Windows.h>
#include <TlHelp32.h>
#include <set>
#include <iostream>	
#include <thread>
#include <chrono>
#include <string>
#include "Psapi.h"

void printLoadedDlls() {
    DWORD pid = GetCurrentProcessId();
    std::set<std::string> printedDlls;

    while (true) {
        std::cout << "Process ID: " << pid << std::endl;
        HMODULE hMods[1024];
        DWORD cbNeeded;

        if (EnumProcessModules(GetCurrentProcess(), hMods, sizeof(hMods), &cbNeeded)) {
            for (unsigned int i = 0; i < (cbNeeded / sizeof(HMODULE)); i++) {
                char szModName[MAX_PATH];
                if (GetModuleFileNameEx(GetCurrentProcess(), hMods[i], szModName, sizeof(szModName) / sizeof(char))) {
                    std::string dllName(szModName);
                    if (printedDlls.find(dllName) == printedDlls.end()) {
                        std::cout << "Loaded DLL: " << dllName << std::endl;
                        printedDlls.insert(dllName);
                    }
                }
            }
        }
        std::this_thread::sleep_for(std::chrono::seconds(1)); 
}

int main() {
    printLoadedDlls();
    return 0;
}
