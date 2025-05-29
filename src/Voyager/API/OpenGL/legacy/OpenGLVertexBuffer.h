// #pragma once
// // OpenGL
// #include <Glad/glad.h>
// #include <GLFW/glfw3.h>

// #include "OpenGLBufferEnum.h"

// namespace Voyager {

//     class OpenGLVertexBuffer {
//     private:
//         unsigned int m_RendererID;
//         unsigned int m_Size;
//         OpenGLBufferUsage m_Usage; // GL_STATIC_DRAW, GL_DYNAMIC_DRAW, GL_STREAM_DRAW, etc.

//         // m_Data is out of sync with the GPU buffer
//         // only used for total buffer recreation
//         void* m_Data;
//     public:
//         OpenGLVertexBuffer();
//         OpenGLVertexBuffer(void* data, unsigned int size);
//         ~OpenGLVertexBuffer();
        
//         // does not change GPU buffer
//         void ProvideBufferData(void* data, unsigned int size);
//         void SetUsage(OpenGLBufferUsage usage); // would want to replace this with custom enum
        
//         // called by the renderer --> needs context current
//         void Generate();
//         void BindBufferData() const; // total recreation of the buffer
//         void Bind() const;
//         void Unbind() const;
//         void* MapBuffer(OpenGLBufferAccess access) const; // direct access to the GPU buffer data
//         void UnmapBuffer() const;
        
//         inline unsigned int GetSize() const { return m_Size; }
//     };
// }