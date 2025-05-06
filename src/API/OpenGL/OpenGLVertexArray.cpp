// OpenGL
#include <Glad/glad.h>
#include <GLFW/glfw3.h>

#include "OpenGLVertexArray.h"

namespace Voyager {
        
    OpenGLVertexArray::OpenGLVertexArray(): m_RendererID(0) {}

    OpenGLVertexArray::~OpenGLVertexArray() {
        if(m_RendererID != 0) glDeleteVertexArrays(1, &m_RendererID);
    }

    void OpenGLVertexArray::Generate() {
        if(m_RendererID != 0) return;
        glGenVertexArrays(1, &m_RendererID);
        glBindVertexArray(m_RendererID);
    }

    void OpenGLVertexArray::AddBuffer(const OpenGLVertexBuffer& vb, const OpenGLVertexBufferLayout& layout) const {
        Bind();
        vb.Bind();
        const auto& elements = layout.GetElements();
        unsigned int offset = 0;
        for(int i=0; i<elements.size(); i++) {
            const auto& element = elements[i];
            glEnableVertexAttribArray(i);
            glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), reinterpret_cast<const void*>(offset));
            offset += OpenGLVertexBufferElement::GetSizeOfType(element.type) * element.count;
        }
    }
    void OpenGLVertexArray::Bind() const {
        glBindVertexArray(m_RendererID);
    }
    void OpenGLVertexArray::Unbind() const {
        glBindVertexArray(0);
    }
}