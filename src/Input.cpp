#include "Input.h"

#include <cassert>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

Input* g_input = nullptr;

Key vk_to_keycode(u8 vk)
{
    // Direct mappings for letters and numbers
    if ((vk >= 'A' && vk <= 'Z') || (vk >= '0' && vk <= '9'))
    {
        return static_cast<Key>(vk);
    }

    switch (vk)
    {
        case VK_SPACE:  return Key::Space;
        case VK_LEFT:   return Key::Left;
        case VK_RIGHT:  return Key::Right;
        case VK_UP:     return Key::Up;
        case VK_DOWN:   return Key::Down;
        case VK_SHIFT:  return Key::Shift;
        case VK_CONTROL: return Key::Control;
        case VK_MENU:    return Key::Alt;
        default:        return Key::Count;
    }
}

bool Input::initialize(void* hWnd)
{
    assert(m_hWnd == nullptr);
    assert(g_input == nullptr);

    g_input = this;

    m_hWnd = hWnd;

    RAWINPUTDEVICE rid;
    rid.usUsagePage = 0x01;
    rid.usUsage = 0x06;
    rid.dwFlags = RIDEV_NOLEGACY;
    rid.hwndTarget = (HWND)hWnd;

    return RegisterRawInputDevices(&rid, 1, sizeof(rid));
}

void Input::handle_raw_input(i64 lParam)
{
    // Process raw input
    u8 buffer[1024];
    UINT size = sizeof(buffer); 
    u32 dataSize;
    GetRawInputData((HRAWINPUT)lParam, RID_INPUT, NULL, &dataSize, sizeof(RAWINPUTHEADER));
    
    if (GetRawInputData((HRAWINPUT)lParam, RID_INPUT, buffer, &dataSize, sizeof(RAWINPUTHEADER)) == dataSize) 
    {
        RAWINPUT* raw = (RAWINPUT*)buffer;

        if (raw->header.dwType == RIM_TYPEKEYBOARD) {
            // Process keyboard input
            RAWKEYBOARD& rawKeyboard = raw->data.keyboard;
            
            // For example, check the virtual key code and key state
            if (rawKeyboard.Flags & RI_KEY_BREAK) {
                // Key up event
            } else {
                // Key down event
            }
        }
        else if (raw->header.dwType == RIM_TYPEMOUSE) {
            // Process mouse input
            RAWMOUSE& rawMouse = raw->data.mouse;
            
            // Use rawMouse.lLastX and rawMouse.lLastY for mouse movement
        }
    }
}

void Input::update()
{
    for (auto& key : m_keys)
    {
        key.bPressed = false;
    }

   
}

Input::KeyState Input::get_key(Key key)
{
    return g_input->m_keys[(u8)key];
}