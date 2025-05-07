#include "BasicTextureRenderer.h"

namespace Voyager {

    BasicTextureRenderer::BasicTextureRenderer(OpenGLWindow& window): BasicRenderer(window) {}
    BasicTextureRenderer::~BasicTextureRenderer() {}

    void BasicTextureRenderer::AddTexture(OpenGLTexture& texture, const std::string& name, int slot) {
        m_Window->MakeWindowContextCurrent();
        m_Shader->Bind();
        texture.Generate();
        m_Shader->SetUniform1i("u_Texture_" + name, slot);
        m_Texture = &texture;
    }
    void BasicTextureRenderer::Draw() const {
        m_Shader->Bind();
        m_Texture->Bind();
        m_VertexArray->Bind();
        m_IndexBuffer->Bind();
        glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);
    }
}