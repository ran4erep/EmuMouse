#include <windows.h>
#include <shellapi.h>

#define WM_TRAYICON (WM_USER + 1)
#define ID_TRAY_EXIT 1001
#define IDI_ICON1 101

HHOOK keyboardHook;
bool isWindowsKeyPressed = false;
HWND hwnd;
NOTIFYICONDATA nid;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_TRAYICON: {
            if (lParam == WM_RBUTTONUP || lParam == WM_LBUTTONUP) {
                POINT pt;
                GetCursorPos(&pt);
                HMENU menu = CreatePopupMenu();
                InsertMenu(menu, -1, MF_BYPOSITION | MF_STRING, ID_TRAY_EXIT, "Exit");
                SetForegroundWindow(hwnd);
                TrackPopupMenu(menu, TPM_RIGHTALIGN | TPM_BOTTOMALIGN, pt.x, pt.y, 0, hwnd, NULL);
                DestroyMenu(menu);
            }
            return 0;
        }
        case WM_COMMAND: {
            if (LOWORD(wParam) == ID_TRAY_EXIT) {
                Shell_NotifyIcon(NIM_DELETE, &nid);
                PostQuitMessage(0);
            }
            return 0;
        }
        case WM_DESTROY: {
            Shell_NotifyIcon(NIM_DELETE, &nid);
            PostQuitMessage(0);
            return 0;
        }
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode >= 0) {
        KBDLLHOOKSTRUCT* kbStruct = (KBDLLHOOKSTRUCT*)lParam;
        
        if (kbStruct->vkCode == VK_LWIN || kbStruct->vkCode == VK_RWIN) {
            if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) {
                isWindowsKeyPressed = true;
            } else if (wParam == WM_KEYUP || wParam == WM_SYSKEYUP) {
                isWindowsKeyPressed = false;
            }
        }

        if (isWindowsKeyPressed && (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN)) {
            if (kbStruct->vkCode == 'Q') {
                mouse_event(MOUSEEVENTF_WHEEL, 0, 0, 120, 0);
                return 1;
            }
            else if (kbStruct->vkCode == 'A') {
                mouse_event(MOUSEEVENTF_WHEEL, 0, 0, -120, 0);
                return 1;
            }
        }
    }
    return CallNextHookEx(keyboardHook, nCode, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASSEX wc = {0};
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "EmuMouseClass";
    
    if (!RegisterClassEx(&wc)) return 1;

    hwnd = CreateWindowEx(0, "EmuMouseClass", "EmuMouse", 
                         WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
                         CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

    if (!hwnd) return 1;

    nid.cbSize = sizeof(NOTIFYICONDATA);
    nid.hWnd = hwnd;
    nid.uID = 1;
    nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
    nid.uCallbackMessage = WM_TRAYICON;
    nid.hIcon = (HICON)LoadImage(hInstance, 
                            MAKEINTRESOURCE(IDI_ICON1),
                            IMAGE_ICON,
                            16,
                            16,
                            LR_DEFAULTCOLOR);
    strcpy(nid.szTip, "EmuMouse (Win+Q/A)");

    Shell_NotifyIcon(NIM_ADD, &nid);

    keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, NULL, 0);
    if (!keyboardHook) {
        Shell_NotifyIcon(NIM_DELETE, &nid);
        return 1;
    }

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    UnhookWindowsHookEx(keyboardHook);
    return 0;
}