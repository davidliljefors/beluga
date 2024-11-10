#include "dx11.h"
#include "Camera.h"
#include "TriangleRenderer.h"


#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <d3d11.h>
#include <dxgi1_6.h>

#include <cstdio>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")

D3D11Core::D3D11Core(void* hwnd, int width, int height) 
{
    HRESULT hr = CreateDXGIFactory2(0, __uuidof(IDXGIFactory), (void**)&m_pFactory);
    check_dx_error(hr, "CreateDXGIFactory");

    CHECK_DX(D3D11CreateDevice,
        nullptr, 
        D3D_DRIVER_TYPE_HARDWARE, 
        nullptr, 
        D3D11_CREATE_DEVICE_DEBUG, 
        nullptr, 
        0, 
        D3D11_SDK_VERSION, 
        &m_pDevice, 
        nullptr, 
        &m_pDeviceContext
    );

#ifdef _DEBUG
    ID3D11InfoQueue* pInfoQueue = nullptr;

    CHECK_DX(m_pDevice->QueryInterface, __uuidof(ID3D11Debug), (void**)&m_pDebug);
    CHECK_DX(m_pDebug->QueryInterface, __uuidof(ID3D11InfoQueue), (void**)&pInfoQueue);
    CHECK_DX(pInfoQueue->SetBreakOnSeverity, D3D11_MESSAGE_SEVERITY_CORRUPTION, true);
    CHECK_DX(pInfoQueue->SetBreakOnSeverity, D3D11_MESSAGE_SEVERITY_ERROR, true);
    CHECK_DX(pInfoQueue->SetBreakOnSeverity, D3D11_MESSAGE_SEVERITY_WARNING, true);
    
    pInfoQueue->Release();
    puts("D3D11 debug layer enabled successfully");
	
#endif
    
    // Create swap chain
    DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
	swapChainDesc.BufferCount = 2;
	swapChainDesc.BufferDesc.Width = width;
	swapChainDesc.BufferDesc.Height = height;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.RefreshRate = {144, 1};
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = (HWND)hwnd;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.Windowed = TRUE;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;

    CHECK_DX(m_pFactory->CreateSwapChain, m_pDevice, &swapChainDesc, &m_pSwapChain);

	resize(width, height);

    m_pCamera = new Camera();
}

D3D11Core::~D3D11Core() 
{
    m_pTriangleRenderer->shutdown();

    if (m_pDeviceContext) m_pDeviceContext->Release();
    if (m_pSwapChain) m_pSwapChain->Release();
    if (m_pFactory) m_pFactory->Release();
    if (m_pRenderTargetView) m_pRenderTargetView->Release();
    if (m_pDevice) m_pDevice->Release();

    if(m_pDebug) 
    {
        m_pDebug->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);
        m_pDebug->Release();
    }
}

void D3D11Core::render_frame()
{
    m_pDeviceContext->ClearRenderTargetView(m_pRenderTargetView, m_clearColor);

    m_pDeviceContext->OMSetRenderTargets(1, &m_pRenderTargetView, nullptr);

    m_pTriangleRenderer->render(m_pDeviceContext);

    CHECK_DX(m_pSwapChain->Present, 2, 0);
}

void D3D11Core::resize(u32 width, u32 height)
{
    if (!m_pSwapChain) return;

    printf("Resizing DX11 Core to %u x %u\n", width, height);

    // Release render target
    if (m_pRenderTargetView) {
        m_pRenderTargetView->Release();
        m_pRenderTargetView = nullptr;
    }

    // Resize swap chain buffers
    CHECK_DX(m_pSwapChain->ResizeBuffers, BUFFER_COUNT, width, height, DXGI_FORMAT_R8G8B8A8_UNORM, 0);

    // Recreate render target view
    create_render_target_view();

    // Update viewport
    D3D11_VIEWPORT viewport = {};
    viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;
    viewport.Width = (float)width;
    viewport.Height = (float)height;
    viewport.MinDepth = 0.0f;
    viewport.MaxDepth = 1.0f;
    m_pDeviceContext->RSSetViewports(1, &viewport);
}

void D3D11Core::create_triangle_renderer() 
{
  m_pTriangleRenderer = new TriangleRenderer();
  m_pTriangleRenderer->initialize(m_pDevice);
}

void D3D11Core::create_render_target_view()
{
    if (m_pRenderTargetView) {
        m_pRenderTargetView->Release();
        m_pRenderTargetView = nullptr;
    }

    ID3D11Texture2D* pBackBuffer;
    CHECK_DX(m_pSwapChain->GetBuffer, 0, __uuidof(ID3D11Texture2D), (void**)&pBackBuffer);

    CHECK_DX(m_pDevice->CreateRenderTargetView, pBackBuffer, nullptr, &m_pRenderTargetView);

	pBackBuffer->Release();
}

bool D3D11Core::check_dx_error(HRESULT hr, const char* operation)
{
    if (FAILED(hr))
    {
        // Get error message
        char error_msg[256];
        FormatMessageA(
            FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
            nullptr,
            hr,
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            error_msg,
            sizeof(error_msg),
            nullptr
        );

        printf("DX Error in %s: (0x%08lX) %s\n", operation, hr, error_msg);

        throw "DX Error";
        return true;
    }
    return false;
}