#include "ShaderCompiler.h"

#include <d3d11.h>
#include <d3dcompiler.h>
#include <d3dcommon.h>

#include <cstdio>

thread_local char ShaderCompiler::m_last_error[1024] = {};

bool ShaderCompiler::compile_vertex_shader(
    const char* shader_source,
    const char* entry_point,
    ID3D11Device* p_device,
    ID3D11VertexShader** pp_vertex_shader,
    ID3DBlob** pp_blob_out)
{
    ID3DBlob* p_shader_blob = nullptr;
    if (!compile_shader(shader_source, entry_point, "vs_5_0", &p_shader_blob)) {
        return false;
    }

    HRESULT hr = p_device->CreateVertexShader(
        p_shader_blob->GetBufferPointer(),
        p_shader_blob->GetBufferSize(),
        nullptr,
        pp_vertex_shader
    );

    if (pp_blob_out) {
        *pp_blob_out = p_shader_blob;
    } else {
        p_shader_blob->Release();
    }

    if (FAILED(hr)) {
        snprintf(m_last_error, sizeof(m_last_error), 
                "Failed to create vertex shader (HRESULT: 0x%08lX)", hr);
        return false;
    }

    return true;
}

bool ShaderCompiler::compile_pixel_shader(
    const char* shader_source,
    const char* entry_point,
    ID3D11Device* p_device,
    ID3D11PixelShader** pp_pixel_shader)
{
    ID3DBlob* p_shader_blob = nullptr;
    if (!compile_shader(shader_source, entry_point, "ps_5_0", &p_shader_blob)) {
        return false;
    }

    HRESULT hr = p_device->CreatePixelShader(
        p_shader_blob->GetBufferPointer(),
        p_shader_blob->GetBufferSize(),
        nullptr,
        pp_pixel_shader
    );

    p_shader_blob->Release();

    if (FAILED(hr)) {
        snprintf(m_last_error, sizeof(m_last_error), 
                "Failed to create pixel shader (HRESULT: 0x%08lX)", hr);
        return false;
    }

    return true;
}

bool ShaderCompiler::compile_shader(
    const char* shader_source,
    const char* entry_point,
    const char* target,
    ID3DBlob** pp_blob_out)
{
    ID3DBlob* p_error_blob = nullptr;
    UINT compile_flags = D3DCOMPILE_ENABLE_STRICTNESS;

#ifdef _DEBUG
    compile_flags |= D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

    HRESULT hr = D3DCompile(
        shader_source,
        strlen(shader_source),
        nullptr,    // source name
        nullptr,    // defines
        nullptr,    // include handler
        entry_point,
        target,
        compile_flags,
        0,          // effect flags
        pp_blob_out,
        &p_error_blob
    );

    if (FAILED(hr)) {
        if (p_error_blob) {
            snprintf(m_last_error, sizeof(m_last_error), "Shader compilation failed: %s",
                    (const char*)p_error_blob->GetBufferPointer());
            p_error_blob->Release();
        } else {
            snprintf(m_last_error, sizeof(m_last_error), 
                    "Shader compilation failed (HRESULT: 0x%08lX)", hr);
        }
        return false;
    }

    if (p_error_blob) p_error_blob->Release();
    return true;
} 