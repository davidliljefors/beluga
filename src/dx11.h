#pragma once

using u32 = unsigned int;


class D3D11Core {
public:
    D3D11Core(void* hwnd, int width, int height);
    ~D3D11Core();

    void Present();

private:
    static constexpr u32 BUFFER_COUNT = 2;
    
    class IDXGIFactory* m_factory = nullptr;
    class ID3D11Device* m_device = nullptr;
    class ID3D11CommandQueue* m_commandQueue = nullptr;
    class IDXGISwapChain* m_swapChain = nullptr;
    class ID3D11DeviceContext* m_deviceContext = nullptr;

    u32 m_currentBackBuffer = 0;
};