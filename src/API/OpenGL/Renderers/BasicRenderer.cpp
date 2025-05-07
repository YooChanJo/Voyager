#include "BasicRenderer.h"

namespace Voyager {
    
    BasicRenderer::BasicRenderer(OpenGLWindow& window): m_Window(&window) {
        m_Window->MakeWindowContextCurrent();
    }
    BasicRenderer::~BasicRenderer() {}

    void BasicRenderer::AddVertexArray(OpenGLVertexArray& vao) {
        m_Window->MakeWindowContextCurrent();
        vao.Generate();
        m_VertexArray = &vao;
    }
    void BasicRenderer::AddVertexBufferAndLayout(OpenGLVertexBuffer& vbo, OpenGLVertexBufferLayout& layout) {
        m_Window->MakeWindowContextCurrent();
        vbo.Generate();
        vbo.BindBufferData(); // the vbo provided is required to have valid data
        m_VertexBuffer = &vbo;
        m_Layout = &layout;
        m_VertexArray->AddBuffer(vbo, layout);
    }
    void BasicRenderer::AddIndexBuffer(OpenGLIndexBuffer& ibo) {
        m_Window->MakeWindowContextCurrent();
        ibo.Generate();
        ibo.BindBufferData(); // the ibo provided is required to have valid data
        m_IndexBuffer = &ibo;
    }
    void BasicRenderer::AddShader(OpenGLShader& shader) {
        m_Window->MakeWindowContextCurrent();
        shader.Generate();
        m_Shader = &shader;
    }

    void BasicRenderer::Draw() const {
        if(m_Window->IsClosed()) return;
        m_Shader->Bind();
        m_VertexArray->Bind();
        m_IndexBuffer->Bind();
        glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);
    }
}