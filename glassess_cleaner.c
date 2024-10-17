#include <windows.h>

#define WIN_WIDTH  1500
#define WIN_HEIGHT 1000

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        // Draw black on the left side
        HBRUSH blackBrush = CreateSolidBrush(RGB(0, 0, 0));
        RECT blackRect = { 0, 0, WIN_WIDTH / 2, WIN_HEIGHT };
        FillRect(hdc, &blackRect, blackBrush);
        DeleteObject(blackBrush);

        // Draw white on the right side
        HBRUSH whiteBrush = CreateSolidBrush(RGB(255, 255, 255));
        RECT whiteRect = { WIN_WIDTH / 2, 0, WIN_WIDTH, WIN_HEIGHT };
        FillRect(hdc, &whiteRect, whiteBrush);
        DeleteObject(whiteBrush);

        EndPaint(hwnd, &ps);
    }
    return 0;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    const char CLASS_NAME[] = "GlassesCleanerWindowClass";

    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0,                              // Optional window styles
        CLASS_NAME,                     // Window class
        "DIRTY NO MORE!",              // Window title
        WS_OVERLAPPEDWINDOW,            // Window style
        CW_USEDEFAULT, CW_USEDEFAULT,   // Position
        WIN_WIDTH, WIN_HEIGHT,          // Size
        NULL,                           // Parent window
        NULL,                           // Menu
        hInstance,                      // Instance handle
        NULL                            // Additional application data
    );

    if (hwnd == NULL)
    {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    MSG msg = { 0 };
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}