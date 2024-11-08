#include "Window.h"
#include <Windows.h>

#include "ShaderCompiler.h"
#include "Camera.h"
#include "TriangleRenderer.h"

int main()
{

    Camera cam;
    cam.set_perspective(60, 800.0f / 600.0f, 0.1f, 100.0f);
    TriangleRenderer* pTriangleRenderer = new TriangleRenderer();

    Window window(800, 600, "Beluga");

    window.get_dx11_core()->create_triangle_renderer();


    while (window.process_messages())
    {
        window.present();
        Sleep(5);
    }
    return 0;
}