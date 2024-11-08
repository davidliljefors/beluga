#include "Window.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    switch (msg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            // Create a black brush and fill the window with it
            HBRUSH blackBrush = CreateSolidBrush(RGB(0, 0, 0));
            FillRect(hdc, &ps.rcPaint, blackBrush);
            DeleteObject(blackBrush);  // Clean up the brush
            EndPaint(hwnd, &ps);
        }
        return 0;
    }
    return DefWindowProc(hwnd, msg, wparam, lparam);
}

Window::Window(int width, int height, const char* title)
    : m_width(width)
    , m_height(height)
    , m_title(title)
{
    // Register window class
    WNDCLASSEX wc = {};
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(nullptr);
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.lpszClassName = "BelugaWindowClass";
    RegisterClassEx(&wc);

    // Create window
    RECT wr = { 0, 0, width, height };
    AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);

    m_hwnd = CreateWindowEx(
        0,                              // Optional window styles
        "BelugaWindowClass",            // Window class
        title,                          // Window text
        WS_OVERLAPPEDWINDOW,            // Window style
        CW_USEDEFAULT,                  // X
        CW_USEDEFAULT,                  // Y
        wr.right - wr.left,             // Width
        wr.bottom - wr.top,             // Height
        nullptr,                        // Parent window    
        nullptr,                        // Menu
        GetModuleHandle(nullptr),       // Instance handle
        this                            // Additional application data
    );

    ShowWindow((HWND)m_hwnd, SW_SHOW);
}

Window::~Window()
{
    if (m_hwnd) DestroyWindow((HWND)m_hwnd);
}

bool Window::ProcessMessages()
{
    MSG msg = {};
    while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
    {
        if (msg.message == WM_QUIT)
            return false;

        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return true;
}

