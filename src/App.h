#pragma once

#include "Core.h"


class D3D11Core;
class Input;
class GuiPanel;
class RenderScene;

class App {
public:
    App(i32 width, i32 height, const char* title);
    ~App();

    void register_panel(GuiPanel* pPanel);

    bool process_messages();
    void update();

    D3D11Core* get_dx11_core() const { return m_pDx11Core; }
    void* get_hwnd() const { return m_hwnd; }
    Input* get_input() const { return m_pInput; }

private:

private:
    void* m_hwnd;
    i32 m_width;
    i32 m_height;
    const char* m_title;
    D3D11Core* m_pDx11Core;
    Input* m_pInput;

};
