#include <Windows.h>
#include "Application.h"
#include "ActiveWindowKiller.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    return Application::app_main();
}

int main() {
    return Application::app_main();
}