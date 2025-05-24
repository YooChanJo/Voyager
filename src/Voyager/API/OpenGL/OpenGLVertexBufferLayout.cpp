#include "OpenGLVertexBufferLayout.h"

namespace Voyager {
    unsigned int OpenGLVertexBufferElement::GetSizeOfType(unsigned int type) {
        switch (type) {
            case GL_FLOAT: return sizeof(GLfloat);
            case GL_UNSIGNED_INT: return sizeof(GLuint);
            case GL_UNSIGNED_BYTE: return sizeof(GLubyte);
        }
        return 0;
    }
    template<typename T>
    void OpenGLVertexBufferLayout::Push(unsigned int count) {
        static_assert(false);
    }

    template<>
    void OpenGLVertexBufferLayout::Push<float>(unsigned int count) {
        m_Elements.push_back({ GL_FLOAT, count, GL_FALSE });
        m_Stride += OpenGLVertexBufferElement::GetSizeOfType(GL_FLOAT) * count;
    }

    template<>
    void OpenGLVertexBufferLayout::Push<unsigned int>(unsigned int count) {
        m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
        m_Stride += OpenGLVertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT) * count;
    }

    template<>
    void OpenGLVertexBufferLayout::Push<unsigned char>(unsigned int count) {
        m_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
        m_Stride += OpenGLVertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE) * count;
    }
}