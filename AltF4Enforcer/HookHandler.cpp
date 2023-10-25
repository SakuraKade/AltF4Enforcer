#include <iostream>
#include <Windows.h>
#include "ActiveWindowKiller.h"
#include "HookHandler.h"

HHOOK keyboardHook;

LRESULT CALLBACK KeyboardHookCallback(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode >= 0) {
        KBDLLHOOKSTRUCT* kbdStruct = reinterpret_cast<KBDLLHOOKSTRUCT*>(lParam);
        bool altDown = (kbdStruct->flags & LLKHF_ALTDOWN) != 0;
        int keyCode = kbdStruct->vkCode;

        const int KEY_DOWN = 0x104;

        if (altDown && keyCode == VK_F4 && wParam == KEY_DOWN) {
            // Kill the currently focused application here
            std::cout << "Alt + F4 pressed" << std::endl;
            bool killSuccess = ActiveWindowKiller::kill();

            if (killSuccess == false) {
                // Forward the Alt + F4 message
                return CallNextHookEx(keyboardHook, nCode, wParam, lParam);
            }

            // Unhook and rehook to prevent the message being sent to the wrong application.
            UnhookWindowsHookEx(keyboardHook);
            keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardHookCallback, nullptr, 0);

            // Return 1 to prevent the message from being forwarded
            return 1;
        }
    }

    return CallNextHookEx(keyboardHook, nCode, wParam, lParam);
}

HookHandler::HookHandler()
{
    keyboardHook = nullptr;
}

HookHandler::~HookHandler()
{
    this->unhook();
}

void HookHandler::hook()
{
    keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardHookCallback, nullptr, 0);
    if (keyboardHook == nullptr) {
        // Handle error: failed to set the keyboard hook
        std::cerr << "Failed to set the keyboard hook" << std::endl;
    }

}

void HookHandler::unhook()
{
    if (keyboardHook != nullptr) {
        if (!UnhookWindowsHookEx(keyboardHook)) {
            // Handle error: failed to unhook the keyboard hook
            std::cerr << "Failed to unhook the keyboard hook" << std::endl;
        }
        keyboardHook = nullptr;
    }
}
