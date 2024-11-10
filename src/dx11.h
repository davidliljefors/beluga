#pragma once

using u32 = unsigned int;
using HRESULT = long;

#define CONCAT_IMPL(a, b) a##b
#define CONCAT(a, b) CONCAT_IMPL(a, b)

#define UNIQUENAME(prefix) CONCAT(prefix, __LINE__)

#define CHECK_DX(func, ...) \
    HRESULT UNIQUENAME(hr_) = func(__VA_ARGS__); \
    D3D11Core::check_dx_error(UNIQUENAME(hr_), #func)

class D3D11Core {
public:
    D3D11Core(void* hwnd, int width, int height);
    
    D3D11Core(const D3D11Core&) = delete;
    D3D11Core(D3D11Core&&) = delete;
    D3D11Core& operator=(const D3D11Core&) = delete;
    D3D11Core& operator=(D3D11Core&&) = delete;

    ~D3D11Core();

    void render_frame();
    void resize(u32 width, u32 height);

    struct ID3D11Device* get_device() const { return m_pDevice; }
    struct ID3D11DeviceContext* get_device_context() const { return m_pDeviceContext; }


    void create_triangle_renderer();

    static bool check_dx_error(HRESULT hr, const char* operation);

private:
    static constexpr u32 BUFFER_COUNT = 2;

    void create_render_target_view();
    
    struct IDXGIFactory* m_pFactory = nullptr;
    struct ID3D11Device* m_pDevice = nullptr;
    struct ID3D11CommandQueue* m_commandQueue = nullptr;
    struct IDXGISwapChain* m_pSwapChain = nullptr;
    struct ID3D11DeviceContext* m_pDeviceContext = nullptr;
    struct ID3D11Debug* m_pDebug = nullptr;

    u32 m_currentBackBuffer = 0;

    struct ID3D11RenderTargetView* m_pRenderTargetView = nullptr;

    class TriangleRenderer* m_pTriangleRenderer = nullptr;
    class Camera* m_pCamera = nullptr;

    float m_clearColor[4] = {0.2f, 0.2f, 0.2f, 1.0f};
    float m_time = 0.0f;

};