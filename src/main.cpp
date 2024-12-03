#include "App.h"

#include <cstdio>
#include <cstring>

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>

#include "FreeCamera.h"
#include "Input.h"
#include "dx11.h"

struct DeltaTime
{
	
};

int main(int argc, char** argv)
{
    bool bWaitForDebugger = false;
    
    for (int i = 1; i < argc; ++i)
    {
        if (strcmp(argv[i], "-waitForDebugger") == 0)
        {
            bWaitForDebugger = true;
            break;
        }
    }

    if (bWaitForDebugger)
    {
        puts("Waiting for debugger...\n");
        while (!IsDebuggerPresent())
        {
            Sleep(10);
        }
        if (IsDebuggerPresent())
        {
            puts("Debugger attached!\n");
        }
    }

    FreeCamera cam;
    cam.set_perspective(60, 800.0f / 600.0f, 0.1f, 100.0f);

    App app(800, 600, "Beluga");

    while (app.process_messages())
    {
        if(Input::get_key(Key::Space).bHeld)
        {
            puts("Space pressed");
        }
        
        app.update();
        Sleep(5);
    }
    return 0;
}