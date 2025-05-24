#include "OpenGLIndexBuffer.h"

namespace Voyager {

    OpenGLIndexBuffer::OpenGLIndexBuffer(): m_Data(nullptr), m_Count(0), m_RendererID(0), m_Usage(OpenGLBufferUsage::StaticDraw) {}
    OpenGLIndexBuffer::OpenGLIndexBuffer(unsigned int* data, unsigned int count): m_Data(data), m_Count(count), m_RendererID(0), m_Usage(OpenGLBufferUsage::StaticDraw) {}

    OpenGLIndexBuffer::~OpenGLIndexBuffer() {
        if(m_RendererID != 0) glDeleteBuffers(1, &m_RendererID);
    }

    void OpenGLIndexBuffer::SetUsage(OpenGLBufferUsage usage) {
        m_Usage = usage;
    }

    void OpenGLIndexBuffer::Generate() {
        if(m_RendererID != 0) return; // no recreation of buffer
        glGenBuffers(1, &m_RendererID); // generator one buffer
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID); // activate that buffer

    }
    void OpenGLIndexBuffer::ProvideBufferData(unsigned int* data, unsigned int count) {
        m_Data = data; m_Count = count;
    }
    void OpenGLIndexBuffer::BindBufferData() const {
        if(m_RendererID == 0 || m_Count == 0) return; // buffer should be created and data should be provided
        Bind();
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Count * sizeof(unsigned int), m_Data, (GLenum)m_Usage); // DEFAULT bind data to buffer
    };

    void OpenGLIndexBuffer::Bind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID); // activate that buffer
    }

    void OpenGLIndexBuffer::Unbind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // activate that buffer
    }
}