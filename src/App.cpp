#include "App.h"

#include "Input.h"

#include "RenderScene.h"
#include "dx11.h"

#include <cstdio>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    App* pWindow = reinterpret_cast<App*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
    
    switch (msg)
    {
    case WM_CREATE:
    {
        CREATESTRUCT* pCreateStruct = reinterpret_cast<CREATESTRUCT*>(lparam);
        SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pCreateStruct->lpCreateParams));
        return 0;
    }
    case WM_SIZE:
        if (pWindow && pWindow->get_dx11_core())
        {
            UINT width = LOWORD(lparam);
            UINT height = HIWORD(lparam);
            pWindow->get_dx11_core()->resize(width, height);
        }
        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    case WM_INPUT:
        pWindow->get_input()->handle_raw_input(lparam);
        return 0;
    }

    return DefWindowProc(hwnd, msg, wparam, lparam);
}

App::App(int width, int height, const char* title)
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

    m_pInput = new Input();

    m_pInput->initialize(m_hwnd);

    m_pDx11Core = new D3D11Core(m_hwnd, width, height);
}

App::~App()
{
	delete (m_pDx11Core);
	delete m_pInput;
    DestroyWindow((HWND)m_hwnd);
}

bool App::process_messages()
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

void App::update()
{
    m_pDx11Core->pre_render();
    m_pDx11Core->draw();
    m_pDx11Core->present();
}

