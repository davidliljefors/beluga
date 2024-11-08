#include "Window.h"
#include <Windows.h>

int main()
{
    Window window(800, 600, "Beluga");


    while (window.ProcessMessages())
    {
        // TODO: Render
        Sleep(10);
    }
    return 0;
}