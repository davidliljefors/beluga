#include "dx11.h"

#include <stdexcept>
#include <d3d11.h>
#include <dxgi.h>
#include <dxgi.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")

D3D11Core::D3D11Core(void* hwnd, int width, int height) {
    // Create DXGI Factory
    if (FAILED(CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&m_factory))) {
        throw std::runtime_error("Failed to create DXGI factory");
    }

    // Create Device
    if (FAILED(D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, nullptr, 0, D3D11_SDK_VERSION, &m_device, nullptr, &m_deviceContext))) {
        throw std::runtime_error("Failed to create D3D11 device");
    }   
    
}

D3D11Core::~D3D11Core() {
    if (m_deviceContext) m_deviceContext->Release();
    if (m_swapChain) m_swapChain->Release();
    if (m_device) m_device->Release();
    if (m_factory) m_factory->Release();
}

void D3D11Core::Present() {
    m_swapChain->Present(1, 0);
    m_currentBackBuffer = m_swapChain->Present(1, 0);
}