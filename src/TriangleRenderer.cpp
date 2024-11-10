#include "TriangleRenderer.h"

#include <d3d11.h>
#include <d3dcompiler.h>

#include "dx11.h"

#include "Vec3.h"
#include "Vec4.h"

struct Vertex
{
	Vec3 position;
	Vec4 color;
};

namespace
{
const char* kVertexShader = R"(
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
			output.Color.r = 0.8f;
            return output;
        }
    )";

const char* kPixelShader = R"(
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
	: m_pVertexBuffer(nullptr)
	, m_pVertexShader(nullptr)
	, m_pPixelShader(nullptr)
	, m_pInputLayout(nullptr)
{
}

TriangleRenderer::~TriangleRenderer()
{
	shutdown();
}

bool TriangleRenderer::initialize(ID3D11Device* pDevice)
{
	if (!create_vertex_buffer(pDevice)) return false;
	if (!create_shaders(pDevice)) return false;
	return true;
}

void TriangleRenderer::render(ID3D11DeviceContext* pContext)
{
	u32 stride = sizeof(Vertex);
	u32 offset = 0;
	pContext->IASetInputLayout(m_pInputLayout);

	pContext->VSSetShader(m_pVertexShader, nullptr, 0);
	pContext->PSSetShader(m_pPixelShader, nullptr, 0);

	pContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);
	pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	pContext->Draw(3, 0);
}

void TriangleRenderer::shutdown()
{
	if (m_pVertexBuffer) m_pVertexBuffer->Release();
	if (m_pVertexShader) m_pVertexShader->Release();
	if (m_pPixelShader) m_pPixelShader->Release();
	if (m_pInputLayout) m_pInputLayout->Release();

	m_pVertexBuffer = nullptr;
	m_pVertexShader = nullptr;
	m_pPixelShader = nullptr;
	m_pInputLayout = nullptr;
}

bool TriangleRenderer::create_vertex_buffer(ID3D11Device* pDevice)
{
// Define the triangle vertices (centered at 0,0)
	Vertex vertices[] = {
		{ Vec3(0.5f, -0.5f, 0.5f),	Vec4(0.0f, 0.0f, 1.0f, 1.0f) },  // Bottom right (blue)
		{ Vec3(-0.5f, -0.5f, 0.5f), Vec4(0.0f, 1.0f, 0.0f, 1.0f) },  // Bottom left (green)
		{ Vec3(0.0f,  0.5f, 0.5f),	Vec4(1.0f, 0.0f, 0.0f, 1.0f) },  // Top (red)
	};

	D3D11_BUFFER_DESC bd = {};
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(vertices);
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA init_data = {};
	init_data.pSysMem = vertices;

	CHECK_DX(pDevice->CreateBuffer, &bd, &init_data, &m_pVertexBuffer);
	return true;
}

bool TriangleRenderer::create_shaders(ID3D11Device* pDevice)
{
	ID3DBlob* pVsBlob = nullptr;
	ID3DBlob* pErrorBlob = nullptr;

	UINT compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;

	CHECK_DX(D3DCompile,
		kVertexShader,
		strlen(kVertexShader),
		nullptr,
		nullptr,
		nullptr,
		"main",
		"vs_5_0",
		compileFlags,
		0,
		&pVsBlob,
		&pErrorBlob
	);

	if (pErrorBlob)
		pErrorBlob->Release();

	CHECK_DX(pDevice->CreateVertexShader,
		pVsBlob->GetBufferPointer(),
		pVsBlob->GetBufferSize(),
		nullptr, &m_pVertexShader);

	D3D11_INPUT_ELEMENT_DESC layout[] = {
		{ 
			"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,
		  D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12,
		  D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	CHECK_DX(pDevice->CreateInputLayout,
		layout,
		2,
		pVsBlob->GetBufferPointer(),
		pVsBlob->GetBufferSize(),
		&m_pInputLayout);

	pVsBlob->Release();

	ID3DBlob* pPsBlob = nullptr;
	CHECK_DX(D3DCompile,
		kPixelShader,
		strlen(kPixelShader),
		nullptr,
		nullptr,
		nullptr,
		"main",
		"ps_5_0",
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,
		0,
		&pPsBlob,
		&pErrorBlob);

	if (pErrorBlob)
		pErrorBlob->Release();

	CHECK_DX(pDevice->CreatePixelShader,
		pPsBlob->GetBufferPointer(),
		pPsBlob->GetBufferSize(),
		nullptr, &m_pPixelShader);

	pPsBlob->Release();

	return true;
}