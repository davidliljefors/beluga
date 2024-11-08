#include "dx11.h"
#include "TriangleRenderer.h"

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
    
    // Create swap chain
    DXGI_SWAP_CHAIN_DESC swap_chain_desc = {};
    swap_chain_desc.BufferCount = BUFFER_COUNT;
    swap_chain_desc.BufferDesc.Width = width;
    swap_chain_desc.BufferDesc.Height = height;
    swap_chain_desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swap_chain_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swap_chain_desc.OutputWindow = (HWND)hwnd;
    swap_chain_desc.SampleDesc.Count = 1;
    swap_chain_desc.Windowed = TRUE;

    m_factory->CreateSwapChain(m_device, &swap_chain_desc, &m_swapChain);

    // Create render target view
    ID3D11Texture2D* p_back_buffer;
    m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&p_back_buffer);
    m_device->CreateRenderTargetView(p_back_buffer, nullptr, &m_p_render_target_view);
    p_back_buffer->Release();
}

D3D11Core::~D3D11Core() {
    if (m_deviceContext) m_deviceContext->Release();
    if (m_swapChain) m_swapChain->Release();
    if (m_device) m_device->Release();
    if (m_factory) m_factory->Release();
    if (m_p_render_target_view) m_p_render_target_view->Release();
}

void D3D11Core::Present() {
    m_deviceContext->ClearRenderTargetView(m_p_render_target_view, m_clear_color);

    // Set the render target before drawing
    m_deviceContext->OMSetRenderTargets(1, &m_p_render_target_view, nullptr);

    if(m_pTriangleRenderer)
        m_pTriangleRenderer->render(m_deviceContext);

    m_swapChain->Present(1, 0);
}

void D3D11Core::resize(u32 width, u32 height)
{
    if (!m_swapChain) return;

    printf("Resizing DX11 Core to %u x %u\n", width, height);

    // Release render target
    if (m_p_render_target_view) {
        m_p_render_target_view->Release();
        m_p_render_target_view = nullptr;
    }

    // Resize swap chain buffers
    HRESULT hr = m_swapChain->ResizeBuffers(BUFFER_COUNT, width, height, DXGI_FORMAT_R8G8B8A8_UNORM, 0);
    if (FAILED(hr)) {
        printf("Failed to resize swap chain buffers! HRESULT: 0x%lx\n", hr);
        return;
    }

    // Recreate render target view
    create_render_target_view();

    // Update viewport
    D3D11_VIEWPORT viewport = {};
    viewport.Width = (float)width;
    viewport.Height = (float)height;
    viewport.MinDepth = 0.0f;
    viewport.MaxDepth = 1.0f;
    m_deviceContext->RSSetViewports(1, &viewport);
}

void D3D11Core::create_triangle_renderer() {
    auto tri  = (TriangleRenderer*)malloc(sizeof(TriangleRenderer));

    tri->initialize(m_device);

    if(!m_pTriangleRenderer->initialize(m_device))
        throw std::runtime_error("Failed to initialize TriangleRenderer");
}

void D3D11Core::create_render_target_view()
{
    // Release old view if it exists
    if (m_p_render_target_view) {
        m_p_render_target_view->Release();
        m_p_render_target_view = nullptr;
    }

    // Create new render target view
    ID3D11Texture2D* p_back_buffer;
    m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&p_back_buffer);
    m_device->CreateRenderTargetView(p_back_buffer, nullptr, &m_p_render_target_view);
    p_back_buffer->Release();
}