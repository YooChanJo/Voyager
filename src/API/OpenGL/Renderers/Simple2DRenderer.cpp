#include "Simple2DRenderer.h"

#include "Core/Assert.h"
#include "Core/Log.h"

namespace Voyager {
    
    Simple2DRenderer::Simple2DRenderer(/* OpenGLWindow& window */)/* : Renderer2D(window) */ {
        bool success = Init();
        VG_CORE_ASSERT(success, "Failed to create and initialize Simple2DRenderer");
    }
    Simple2DRenderer::~Simple2DRenderer() {}

    bool Simple2DRenderer::Init() {
        ShaderProgramSource source = {
            "#version 330 core\n"
            "layout(location = 0) in vec4 a_position;\n"
            "layout(location = 1) in vec4 a_color;\n"
            "uniform mat4 u_MVP;\n"
            "out vec4 v_Color;\n"
            "void main() {\n"
            "    gl_Position = u_MVP * a_position;\n"
            "    v_Color = a_color;\n"
            "}\n",
            "#version 330 core\n"
            "layout(location = 0) out vec4 fragColor;\n"
            "in vec4 v_Color;\n"
            "void main() {\n"
            "    fragColor = vec4(v_Color);\n"
            "}\n"
        };
        m_Shader = OpenGLShader(source); // default shader
        m_Shader.Generate();
        m_Shader.Bind();
        m_Shader.SetUniformMat4f("u_MVP", glm::mat4(1.0f)); // default MVP matrix - identity matrix
        return true;
    }

    void Simple2DRenderer::ProvideShader(const std::string& filepath) {
        m_Shader = OpenGLShader(filepath);
        m_Shader.Generate();
    }
    void Simple2DRenderer::ProvideShader(const ShaderProgramSource& source) {
        m_Shader = OpenGLShader(source);
        m_Shader.Generate();
    }

    void Simple2DRenderer::Submit(Renderable2D* renderable) {
        m_RenderQueue.push_back(renderable);
    }

    void Simple2DRenderer::Flush() {
        while (!m_RenderQueue.empty()) {
            Renderable2D* renderable = m_RenderQueue[0];
            OpenGLVertexArray vao;
            const auto& color = renderable->GetColor();

            int r = color.r * 255;
            int g = color.g * 255;
            int b = color.b * 255;
            int a = color.a * 255;

            unsigned c = (a << 24) | (b << 16) | (g << 8) | r; // RGBA to unsigned int

            VertexData vertices[4] = {
                { renderable->GetPosition(), c },
                { renderable->GetPosition() + glm::vec3(renderable->GetSize().x, 0.0f, 0.0f), c },
                { renderable->GetPosition() + glm::vec3(renderable->GetSize().x, renderable->GetSize().y, 0.0f), c },
                { renderable->GetPosition() + glm::vec3(0.0f, renderable->GetSize().y, 0.0f), c }
            };
            unsigned int indices[6] = { 0, 1, 2, 2, 3, 0 };

            OpenGLVertexBuffer vbo(vertices, 4 * sizeof(VertexData));
            OpenGLVertexBufferLayout layout = VertexData::GetLayout();
            
            OpenGLIndexBuffer ibo(indices, 6);

            vao.Generate();
            vbo.Generate();
            vbo.BindBufferData();
            vao.AddBuffer(vbo, layout);
            ibo.Generate();
            ibo.BindBufferData();

            m_Shader.Bind();            

            glDrawElements(GL_TRIANGLES, ibo.GetCount(), GL_UNSIGNED_INT, nullptr);
            m_RenderQueue.pop_front();
        }
    }
    
}