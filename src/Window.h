#pragma once

#include "dx11.h"

class Window {
public:
    Window(int width, int height, const char* title);
    ~Window();

    bool process_messages();
    void present();
    D3D11Core* get_dx11_core() const { return m_p_dx11_core; }
    //HWND GetHandle() const { return m_hwnd; }

private:
    
    void* m_hwnd = nullptr;
    int m_width;
    int m_height;
    const char*m_title;
    D3D11Core* m_p_dx11_core;
};
