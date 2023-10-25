#include "ActiveWindowKiller.h"
#include <Windows.h>
#include <iostream>
#include <string>

bool ActiveWindowKiller::kill()
{
    // Get active window handle
    HWND hForegroundWindow = GetForegroundWindow();
    if (hForegroundWindow == NULL)
    {
        std::cout << "No foreground window" << std::endl;
        return false;
    }

    // Get process ID from window handle
    DWORD dwProcessId;
    GetWindowThreadProcessId(hForegroundWindow, &dwProcessId);

    // Open process handle
    HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, dwProcessId);
    if (hProcess == NULL)
    {
        std::cout << "Failed to open process" << std::endl;
        return false;
    }

    // Terminate process
    const unsigned int SUCCESS_CODE = 0;
    bool result = TerminateProcess(hProcess, SUCCESS_CODE);

    // Close process handle
    CloseHandle(hProcess);

    // Check if process termination was successful
    if (!result) {
        DWORD errorCode = GetLastError();
        std::string errorMessage;
        LPSTR lpMsgBuf = nullptr;
        if (FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
            NULL, errorCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&lpMsgBuf, 0, NULL))
        {
            errorMessage = lpMsgBuf;
            LocalFree(lpMsgBuf);
        }
        else {
            errorMessage = "Unknown error";
        }

        std::cout << "Failed to terminate process. Error code: " << errorCode << ", Error message: " << errorMessage << std::endl;
        return false;
    }

    return true;
}
