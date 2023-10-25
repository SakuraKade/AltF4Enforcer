#pragma GCC optimize("03")

#include <Windows.h>;
#include "Application.h";
#include "ActiveWindowKiller.h";

#ifdef NDEBUG
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    return Application::app_main();
}
#endif

#ifdef DEBUG
int main() {
    return Application::app_main();
}
#endif