#pragma once

#include "d3fwd.h"

class TriangleRenderer {
public:
    TriangleRenderer();
    ~TriangleRenderer();

    bool initialize(ID3D11Device* pDevice);
    void render(ID3D11DeviceContext* pContext);
    void shutdown();

private:
    bool create_vertex_buffer(ID3D11Device* pDevice);
    bool create_shaders(ID3D11Device* pDevice);

    ID3D11Buffer* m_pVertex_buffer;
    ID3D11VertexShader* m_pVertex_shader;
    ID3D11PixelShader* m_pPixel_shader;
    ID3D11InputLayout* m_pInput_layout;
}; 