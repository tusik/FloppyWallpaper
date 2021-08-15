#ifndef WINDOWSUTIL_H
#define WINDOWSUTIL_H

#include <Windows.h>
class WindowsUtil
{
public:
    WindowsUtil();
    static HWND GetWorkerW();
    static HWND _WORKERW;
    inline static BOOL CALLBACK EnumWindowsProc(_In_ HWND tophandle, _In_ LPARAM topparamhandle)
    {
        HWND defview = FindWindowEx(tophandle, 0, L"SHELLDLL_DefView", nullptr);
        if (defview != nullptr)
        {
            _WORKERW = FindWindowEx(0, tophandle, L"WorkerW", 0);
        }
        return true;
    }
};

#endif // WINDOWSUTIL_H
