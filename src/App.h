#pragma once

#include "CommonTypes.h"

class D3D11Core;
class Input;

class App {
public:
    App(int width, int height, const char* title);
    ~App();

    bool process_messages();
    void present();
    D3D11Core* get_dx11_core() const { return m_pDx11Core; }
    void* get_hwnd() const { return m_hwnd; }
    Input* get_input() const { return m_pInput; }

private:
    void* m_hwnd = nullptr;
    int m_width;
    int m_height;
    const char*m_title;
    D3D11Core* m_pDx11Core;
    Input* m_pInput;
};
