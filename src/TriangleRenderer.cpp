#include "TriangleRenderer.h"

#include <d3d11.h>
#include <d3dcompiler.h>

#include "Vec3.h"
#include "Vec4.h"

struct Vertex {
    Vec3 position;
    Vec4 color;
};  

namespace {
    const char* k_vertex_shader = R"(
        struct VS_INPUT {
            float3 Position : POSITION;
            float4 Color : COLOR;
        };

        struct VS_OUTPUT {
            float4 Position : SV_POSITION;
            float4 Color : COLOR;
        };

        VS_OUTPUT main(VS_INPUT input) {
            VS_OUTPUT output;
            output.Position = float4(input.Position, 1.0f);
            output.Color = input.Color;
            return output;
        }
    )";

    const char* k_pixel_shader = R"(
        struct PS_INPUT {
            float4 Position : SV_POSITION;
            float4 Color : COLOR;
        };

        float4 main(PS_INPUT input) : SV_Target {
            return input.Color;
        }
    )";
}

TriangleRenderer::TriangleRenderer()
    : m_pVertex_buffer(nullptr)
    , m_pVertex_shader(nullptr)
    , m_pPixel_shader(nullptr)
    , m_pInput_layout(nullptr)
{
}

TriangleRenderer::~TriangleRenderer() {
    shutdown();
}

bool TriangleRenderer::initialize(ID3D11Device* p_device) {
    if (!create_vertex_buffer(p_device)) return false;
    if (!create_shaders(p_device)) return false;
    return true;
}

void TriangleRenderer::render(ID3D11DeviceContext* p_context) {
    // Set the vertex buffer
    u32 stride = sizeof(Vertex);
    u32 offset = 0;
    p_context->IASetVertexBuffers(0, 1, &m_pVertex_buffer, &stride, &offset);
    p_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    p_context->IASetInputLayout(m_pInput_layout);

    // Set the shaders
    p_context->VSSetShader(m_pVertex_shader, nullptr, 0);
    p_context->PSSetShader(m_pPixel_shader, nullptr, 0);

    // Draw the triangle
    p_context->Draw(3, 0);
}

void TriangleRenderer::shutdown() {
    if (m_pVertex_buffer) m_pVertex_buffer->Release();
    if (m_pVertex_shader) m_pVertex_shader->Release();
    if (m_pPixel_shader) m_pPixel_shader->Release();
    if (m_pInput_layout) m_pInput_layout->Release();

    m_pVertex_buffer = nullptr;
    m_pVertex_shader = nullptr;
    m_pPixel_shader = nullptr;
    m_pInput_layout = nullptr;
}

bool TriangleRenderer::create_vertex_buffer(ID3D11Device* pDevice) {
    // Define the triangle vertices (centered at 0,0)
    Vertex vertices[] = {
        { Vec3( 0.0f,  0.5f, 0.0f), Vec4(1.0f, 0.0f, 0.0f, 1.0f) },  // Top (red)
        { Vec3(-0.5f, -0.5f, 0.0f), Vec4(0.0f, 1.0f, 0.0f, 1.0f) },  // Bottom left (green)
        { Vec3( 0.5f, -0.5f, 0.0f), Vec4(0.0f, 0.0f, 1.0f, 1.0f) }   // Bottom right (blue)
    };

    D3D11_BUFFER_DESC bd = {};
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = sizeof(vertices);
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    D3D11_SUBRESOURCE_DATA init_data = {};
    init_data.pSysMem = vertices;

    HRESULT hr = pDevice->CreateBuffer(&bd, &init_data, &m_pVertex_buffer);
    return SUCCEEDED(hr);
}

bool TriangleRenderer::create_shaders(ID3D11Device* pDevice) {
    // Compile vertex shader
    ID3DBlob* p_vs_blob = nullptr;
    ID3DBlob* p_error_blob = nullptr;
    HRESULT hr = D3DCompile(k_vertex_shader, strlen(k_vertex_shader), nullptr, nullptr, nullptr,
                           "main", "vs_4_0", 0, 0, &p_vs_blob, &p_error_blob);
    if (FAILED(hr)) {
        if (p_error_blob) p_error_blob->Release();
        return false;
    }

    hr = pDevice->CreateVertexShader(p_vs_blob->GetBufferPointer(), 
                                     p_vs_blob->GetBufferSize(), 
                                     nullptr, &m_pVertex_shader);
    if (FAILED(hr)) {
        p_vs_blob->Release();
        return false;
    }

    // Create input layout
    D3D11_INPUT_ELEMENT_DESC layout[] = {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, 
          D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, 
          D3D11_INPUT_PER_VERTEX_DATA, 0 }
    };

    hr = pDevice->CreateInputLayout(layout, 2, p_vs_blob->GetBufferPointer(),
                                   p_vs_blob->GetBufferSize(), &m_pInput_layout);
    p_vs_blob->Release();
    if (FAILED(hr)) return false;

    // Compile pixel shader
    ID3DBlob* p_ps_blob = nullptr;
    hr = D3DCompile(k_pixel_shader, strlen(k_pixel_shader), nullptr, nullptr, nullptr,
                    "main", "ps_4_0", 0, 0, &p_ps_blob, &p_error_blob);
    if (FAILED(hr)) {
        if (p_error_blob) p_error_blob->Release();
        return false;
    }

    hr = pDevice->CreatePixelShader(p_ps_blob->GetBufferPointer(),
                                    p_ps_blob->GetBufferSize(),
                                    nullptr, &m_pPixel_shader);
    p_ps_blob->Release();
    return SUCCEEDED(hr);
} 