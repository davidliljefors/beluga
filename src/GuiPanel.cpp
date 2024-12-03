#include "GuiPanel.h"

#include "assert_utils.h"

#define IM_ASSERT(x) BE_ASSERT(x)

#include <imgui/imgui.h>
#include <imgui/imgui_impl_dx11.h>

void imgui_init(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext)
{
    ImGui_ImplDX11_Init(pDevice, pDeviceContext);
}

void imgui_shutdown()
{

}

void on_gui()
{
    ImGui_ImplDX11_NewFrame();
    ImGui::Begin("Hello");
}