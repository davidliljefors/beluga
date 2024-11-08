#pragma once

#include "d3fwd.h"

#include <d3dcommon.h>

class ShaderCompiler {
public:
    static bool compile_vertex_shader(
        const char* shader_source,
        const char* entry_point,
        ID3D11Device* p_device,
        ID3D11VertexShader** pp_vertex_shader,
        ID3DBlob** pp_blob_out = nullptr
    );

    static bool compile_pixel_shader(
        const char* shader_source,
        const char* entry_point,
        ID3D11Device* p_device,
        ID3D11PixelShader** pp_pixel_shader
    );

    static const char* get_last_error() { return m_last_error; }

private:
    static bool compile_shader(
        const char* shader_source,
        const char* entry_point,
        const char* target,
        ID3DBlob** pp_blob_out
    );

    static thread_local char m_last_error[1024];
}; 