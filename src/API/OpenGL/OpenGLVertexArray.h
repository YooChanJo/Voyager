#pragma once

#include "OpenGLVertexBuffer.h"
#include "OpenGLVertexBufferLayout.h"

namespace Voyager {
    
    class OpenGLVertexArray {
    private:
        unsigned int m_RendererID;
    public:
        OpenGLVertexArray();
        ~OpenGLVertexArray();

        // called by the renderer --> needs context current
        void Generate();
        void AddBuffer(const OpenGLVertexBuffer& vb, const OpenGLVertexBufferLayout& layout) const;
        void Bind() const;
        void Unbind() const;
    };

}
