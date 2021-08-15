#include "windowsutil.h"
HWND WindowsUtil::_WORKERW = nullptr;
WindowsUtil::WindowsUtil()
{

}

HWND WindowsUtil::GetWorkerW()
{
    int result;
    HWND windowHandle = FindWindow(L"Progman", nullptr);
    SendMessageTimeout(windowHandle, 0x052c, 0 ,0, SMTO_NORMAL, 0x3e8,(PDWORD_PTR)&result);
    EnumWindows(EnumWindowsProc,(LPARAM)nullptr);
    ShowWindow(_WORKERW,SW_HIDE);
    return windowHandle;
}
