// #include "OpenGLVertexBuffer.h"

// namespace Voyager {

//     OpenGLVertexBuffer::OpenGLVertexBuffer() : m_Data(nullptr), m_Size(0), m_RendererID(0), m_Usage(OpenGLBufferUsage::StaticDraw) {}
//     OpenGLVertexBuffer::OpenGLVertexBuffer(void* data, unsigned int size): m_Data(data), m_Size(size), m_RendererID(0), m_Usage(OpenGLBufferUsage::StaticDraw) {}

//     OpenGLVertexBuffer::~OpenGLVertexBuffer() {
//         if(m_RendererID != 0) glDeleteBuffers(1, &m_RendererID);
//     }
//     void OpenGLVertexBuffer::SetUsage(OpenGLBufferUsage usage) {
//         m_Usage = usage; // would want to replace this with custom enum
//     }

//     void OpenGLVertexBuffer::Generate() {
//         if(m_RendererID != 0) return; // no recreation of buffer
//         glGenBuffers(1, &m_RendererID); // generator one buffer
//         glBindBuffer(GL_ARRAY_BUFFER, m_RendererID); // activate that buffer
//     }
//     void OpenGLVertexBuffer::ProvideBufferData(void* data, unsigned int size) {
//         m_Data = data; m_Size = size;
//     }
//     void OpenGLVertexBuffer::BindBufferData() const {
//         if(m_RendererID == 0 || m_Size == 0) return; // buffer should be created and data should be provided
//         Bind();
//         glBufferData(GL_ARRAY_BUFFER, m_Size, m_Data, (GLenum)m_Usage); // DEFAULT bind data to buffer
//     };

//     void OpenGLVertexBuffer::Bind() const {
//         glBindBuffer(GL_ARRAY_BUFFER, m_RendererID); // activate that buffer
//     }

//     void OpenGLVertexBuffer::Unbind() const {
//         glBindBuffer(GL_ARRAY_BUFFER, 0); // activate that buffer
//     }

//     void* OpenGLVertexBuffer::MapBuffer(OpenGLBufferAccess access) const {
//         return glMapBuffer(GL_ARRAY_BUFFER, (GLenum)access); // direct access to the GPU buffer data
//     }
//     void OpenGLVertexBuffer::UnmapBuffer() const {
//         glUnmapBuffer(GL_ARRAY_BUFFER); // unmap the buffer
//     }
// }
