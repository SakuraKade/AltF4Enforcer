#include <memory>
#include <Windows.h>
#include "HookHandler.h"
#include "Application.h"

int Application::app_main()
{
    std::unique_ptr<HookHandler> hookHandler = std::unique_ptr<HookHandler>::unique_ptr(new HookHandler());
    hookHandler->hook();

    // Message loop
    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0; 
}
