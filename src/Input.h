#pragma once
#include "CommonTypes.h"


enum class Key : u8;

class Input
{
public:
    struct KeyState
    {
        bool bPressed;
        bool bReleased;
        bool bHeld;
    };

    bool initialize(void* hWnd);
    void handle_raw_input(i64 lParam);

    void update();

    static KeyState get_key(Key key); 

private:
    KeyState m_keys[256] = {};
    void* m_hWnd = nullptr;
};

enum class Key : u8
{
    None,
    Left,
    Right,
    Up,
    Down,
    Space,
    Return,
    Escape,
    Backspace,
    Tab,
    Shift,
    Control,
    Alt,
    Count,
    Num0 = '0',
    Num1 = '1',
    Num2 = '2',
    Num3 = '3',
    Num4 = '4',
    Num5 = '5',
    Num6 = '6',
    Num7 = '7',
    Num8 = '8',
    Num9 = '9',
    A = 'A',
    B = 'B',
    C = 'C',
    D = 'D',
    E = 'E',
    F = 'F',
    G = 'G',
    H = 'H',
    I = 'I',
    J = 'J',
    K = 'K',
    L = 'L',
    M = 'M',
    N = 'N',
    O = 'O',
    P = 'P',
    Q = 'Q',
    R = 'R',
    S = 'S',
    T = 'T',
    U = 'U',
    V = 'V',
    W = 'W',
    X = 'X',
    Y = 'Y',
    Z = 'Z',
};