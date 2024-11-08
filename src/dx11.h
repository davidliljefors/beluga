#pragma once

using u32 = unsigned int;


class D3D11Core {
public:
    D3D11Core(void* hwnd, int width, int height);
    ~D3D11Core();

    void Present();
    void resize(u32 width, u32 height);

    struct ID3D11Device* get_device() const { return m_device; }
    struct ID3D11DeviceContext* get_device_context() const { return m_deviceContext; }


    void create_triangle_renderer();

private:
    static constexpr u32 BUFFER_COUNT = 2;

    void create_render_target_view();
    
    struct IDXGIFactory* m_factory = nullptr;
    struct ID3D11Device* m_device = nullptr;
    struct ID3D11CommandQueue* m_commandQueue = nullptr;
    struct IDXGISwapChain* m_swapChain = nullptr;
    struct ID3D11DeviceContext* m_deviceContext = nullptr;

    u32 m_currentBackBuffer = 0;

   struct ID3D11RenderTargetView* m_p_render_target_view = nullptr;

    class TriangleRenderer* m_pTriangleRenderer = nullptr;

    float m_clear_color[4] = {0.0f, 0.0f, 0.0f, 1.0f};
    float m_time = 0.0f;
};