#include "RenderScene.h"

#include <d3d11.h>

#include "Vec3.h"
#include "dx11.h"


struct Vertex
{
    Vec3 pos;
    Vec3 color;
};

Mesh* create_cube_mesh(ID3D11Device* pDevice)
{
    Mesh* pMesh = new Mesh();

    // Define the vertices of the cube
    Vertex vertices[] = {
        { { -1.0f, -1.0f, -1.0f }, { 1.0f, 0.0f, 0.0f } }, // Vertex 0
        { {  1.0f, -1.0f, -1.0f }, { 0.0f, 1.0f, 0.0f } }, // Vertex 1
        { {  1.0f,  1.0f, -1.0f }, { 0.0f, 0.0f, 1.0f } }, // Vertex 2
        { { -1.0f,  1.0f, -1.0f }, { 1.0f, 1.0f, 0.0f } }, // Vertex 3
        { { -1.0f, -1.0f,  1.0f }, { 1.0f, 0.0f, 1.0f } }, // Vertex 4
        { {  1.0f, -1.0f,  1.0f }, { 0.0f, 1.0f, 1.0f } }, // Vertex 5
        { {  1.0f,  1.0f,  1.0f }, { 1.0f, 1.0f, 1.0f } }, // Vertex 6
        { { -1.0f,  1.0f,  1.0f }, { 0.5f, 0.5f, 0.5f } }  // Vertex 7
    };

    // Define the indices for the cube
    u32 indices[] = {
        0, 1, 2, 0, 2, 3, // Back face
        4, 5, 6, 4, 6, 7, // Front face
        0, 3, 7, 0, 7, 4, // Left face
        1, 5, 6, 1, 6, 2, // Right face
        3, 2, 6, 3, 6, 7, // Top face
        0, 4, 5, 0, 5, 1  // Bottom face
    };

    // Create vertex buffer
    D3D11_BUFFER_DESC vertexBufferDesc = {};
    vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    vertexBufferDesc.ByteWidth = sizeof(vertices);
    vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vertexBufferDesc.CPUAccessFlags = 0;

    D3D11_SUBRESOURCE_DATA vertexData = {};
    vertexData.pSysMem = vertices;

    CHECK_DX(pDevice->CreateBuffer, &vertexBufferDesc, &vertexData, &pMesh->m_pVertexBuffer);

    // Create index buffer
    D3D11_BUFFER_DESC indexBufferDesc = {};
    indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    indexBufferDesc.ByteWidth = sizeof(indices);
    indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    indexBufferDesc.CPUAccessFlags = 0;

    D3D11_SUBRESOURCE_DATA indexData = {};
    indexData.pSysMem = indices;

    CHECK_DX(pDevice->CreateBuffer, &indexBufferDesc, &indexData, &pMesh->m_pIndexBuffer);

    pMesh->m_count = ARRAYSIZE(indices);

    return pMesh;
}

RenderScene::RenderScene(D3D11Core* pRenderer_i)
{
    m_pRenderer_i = pRenderer_i;
    
    Mesh* cube = create_cube_mesh(m_pRenderer_i->get_device());

    m_meshes.push_back(cube);
}

void RenderScene::pre_render()
{
    
}

void RenderScene::draw()
{
    u32 stride = sizeof(Vertex);
    u32 offset = 0;

    m_pRenderer_i->get_device_context()->IASetVertexBuffers(0, 1, &m_meshes[0]->m_pVertexBuffer, &stride, &offset);
    m_pRenderer_i->get_device_context()->IASetIndexBuffer(m_meshes[0]->m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
    m_pRenderer_i->get_device_context()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    m_pRenderer_i->get_device_context()->VSSetShader(m_vertexShader, nullptr, 0);
    m_pRenderer_i->get_device_context()->PSSetShader(m_pixelShader, nullptr, 0);
    
    m_pRenderer_i->get_device_context()->DrawIndexed(m_meshes[0]->m_count, 0, 0);
}
