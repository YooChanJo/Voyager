#pragma once
// OpenGL
#include <Glad/glad.h>
#include <GLFW/glfw3.h>

#include "OpenGLBufferEnum.h"

namespace Voyager {
    
    class OpenGLIndexBuffer {
    private:
        unsigned int m_RendererID;
        unsigned int m_Count;
        unsigned int* m_Data;

        OpenGLBufferUsage m_Usage; // GL_STATIC_DRAW, GL_DYNAMIC_DRAW, GL_STREAM_DRAW
    
    public:
        OpenGLIndexBuffer();
        OpenGLIndexBuffer(unsigned int* data, unsigned int count);
        ~OpenGLIndexBuffer(); 

        void SetUsage(OpenGLBufferUsage usage); // would want to replace this with custom enum
            
        void ProvideBufferData(unsigned int* data, unsigned int count);

        // called by the renderer --> needs context current
        void Generate();
        void BindBufferData() const;

        void Bind() const;
        void Unbind() const;
    
        inline void* GetData() const { return m_Data; }
        inline unsigned int GetCount() const { return m_Count; }
    };   
}
