#include "Window.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    Window* window = reinterpret_cast<Window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
    
    switch (msg)
    {
    case WM_CREATE:
    {
        CREATESTRUCT* create = reinterpret_cast<CREATESTRUCT*>(lparam);
        SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(create->lpCreateParams));
        return 0;
    }
    case WM_SIZE:
        if (window && window->get_dx11_core())
        {
            UINT width = LOWORD(lparam);
            UINT height = HIWORD(lparam);
            window->get_dx11_core()->resize(width, height);
        }
        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, msg, wparam, lparam);
}

Window::Window(int width, int height, const char* title)
    : m_width(width)
    , m_height(height)
    , m_title(title)
    , m_pDx11Core(nullptr)
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

    // Create DX11 core after window creation
    m_pDx11Core = new D3D11Core(m_hwnd, width, height);
}

Window::~Window()
{
    delete m_pDx11Core;
    if (m_hwnd) DestroyWindow((HWND)m_hwnd);
}

bool Window::process_messages()
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

void Window::present()
{
    // Present the frame
    m_pDx11Core->render_frame();
}

