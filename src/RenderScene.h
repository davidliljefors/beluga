#pragma once

#include <EASTL/vector.h>

#include "d3fwd.h"

#include "Core.h"

class D3D11Core;

class Mesh
{
    struct Instance
    {
        u32 id;
    };

public:

    u32 add_instance();

    ID3D11Buffer* m_pVertexBuffer;
    ID3D11Buffer* m_pIndexBuffer;
    u32 m_count;
    eastl::vector<Instance> m_instances;
};

class RenderScene
{
public:
    RenderScene(D3D11Core* rendererInterface);

    void pre_render();
    void draw();

private:
    D3D11Core* m_pRenderer_i;
    ID3D11VertexShader* m_pVertexShader;
    ID3D11PixelShader* m_pPixelShader;
    
    eastl::vector<Mesh*> m_meshes;
};