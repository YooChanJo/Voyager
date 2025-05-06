#pragma once

#include <Glad/glad.h>

#include "pch.h"

namespace Voyager {
    struct OpenGLVertexBufferElement {
        unsigned int type;
        unsigned int count;
        unsigned char normalized;
        static unsigned int GetSizeOfType(unsigned int type);
    };

    class OpenGLVertexBufferLayout {
    private:
        std::vector<OpenGLVertexBufferElement> m_Elements;
        unsigned int m_Stride;
    public:
        OpenGLVertexBufferLayout() : m_Stride(0) {}

        template<typename T>
        void Push(unsigned int count);
        inline const std::vector<OpenGLVertexBufferElement> GetElements() const { return m_Elements; }
        inline unsigned int GetStride() const { return m_Stride; }
        
    };

    template<>
    void OpenGLVertexBufferLayout::Push<float>(unsigned int count);
    template<>
    void OpenGLVertexBufferLayout::Push<unsigned int>(unsigned int count);
    template<>
    void OpenGLVertexBufferLayout::Push<unsigned char>(unsigned int count);
}