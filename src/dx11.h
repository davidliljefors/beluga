#pragma once

using u32 = unsigned int;
using HRESULT = long;

#define CONCAT_IMPL(a, b) a##b
#define CONCAT(a, b) CONCAT_IMPL(a, b)

#define UNIQUENAME(prefix) CONCAT(prefix, __LINE__)

#define CHECK_DX(func, ...) \
    HRESULT UNIQUENAME(hr_) = func(__VA_ARGS__); \
    D3D11Core::check_dx_error(UNIQUENAME(hr_), #func)


class ID3D11Device;
class ID3D11DeviceContext;
class IDXGIFactory;
class ID3D11CommandQueue;
class IDXGISwapChain;
class ID3D11Debug;
class ID3D11RenderTargetView;

class FreeCamera;
class RenderScene;

class D3D11Core {
public:
    D3D11Core(void* hWnd, int width, int height);
    
    D3D11Core(const D3D11Core&) = delete;
    D3D11Core(D3D11Core&&) = delete;
    D3D11Core& operator=(const D3D11Core&) = delete;
    D3D11Core& operator=(D3D11Core&&) = delete;

    ~D3D11Core();

    void pre_render();
    void draw();
    void present();
    void resize(u32 width, u32 height);

    ID3D11Device* get_device() const { return m_pDevice; }
    ID3D11DeviceContext* get_device_context() const { return m_pDeviceContext; }

    static bool check_dx_error(HRESULT hr, const char* operation);

private:
    static constexpr u32 BUFFER_COUNT = 2;

    void create_render_target_view();
    void create_render_scene();
    
    IDXGIFactory* m_pFactory = nullptr;
    ID3D11Device* m_pDevice = nullptr;
    ID3D11CommandQueue* m_commandQueue = nullptr;
    IDXGISwapChain* m_pSwapChain = nullptr;
    ID3D11DeviceContext* m_pDeviceContext = nullptr;
    ID3D11Debug* m_pDebug = nullptr;
    
    RenderScene* m_pRenderScene = nullptr;

    u32 m_currentBackBuffer = 0;

    ID3D11RenderTargetView* m_pRenderTargetView = nullptr;

    FreeCamera* m_pFreeCamera = nullptr;

    float m_clearColor[4] = {0.2f, 0.2f, 0.2f, 1.0f};
    float m_time = 0.0f;
};