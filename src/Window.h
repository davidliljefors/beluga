#pragma once

class Window {
public:
    Window(int width, int height, const char* title);
    ~Window();

    bool ProcessMessages();
    //HWND GetHandle() const { return m_hwnd; }

private:
    
    void* m_hwnd = nullptr;
    int m_width;
    int m_height;
    const char*m_title;
};
