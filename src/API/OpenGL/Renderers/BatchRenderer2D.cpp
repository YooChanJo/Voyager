#include "BatchRenderer2D.h"
#include "API/OpenGL/OpenGLBufferEnum.h"

#include "Core/Assert.h"
#include "Core/Log.h"


namespace Voyager {

    BatchRenderer2D::BatchRenderer2D(/* OpenGLWindow& window */)
        // : Renderer2D(window)
    {
        bool success = Init();
        VG_CORE_ASSERT(success, "Failed to create and initialize BatchRenderer2D");
    }

    BatchRenderer2D::~BatchRenderer2D() = default;

    bool BatchRenderer2D::Init() {
        m_VertexArray = std::make_unique<OpenGLVertexArray>();
        m_VertexBuffer = std::make_unique<OpenGLVertexBuffer>(nullptr, RENDERER_BUFFER_SIZE);        
        m_VertexBuffer->SetUsage(OpenGLBufferUsage::DynamicDraw);


        m_VertexBufferLayout = std::make_unique<OpenGLVertexBufferLayout>();
        m_VertexBufferLayout->Push<float>(3); // position
        m_VertexBufferLayout->Push<float>(4); // color

        unsigned int* indices = new unsigned int[RENDERER_INDICES_SIZE];
        
        int offset = 0;
        for(int i = 0; i < RENDERER_MAX_SPRITES; i += 6) {
            indices[  i  ] = offset + 0;
            indices[i + 1] = offset + 1;
            indices[i + 2] = offset + 2;

            indices[i + 3] = offset + 2;
            indices[i + 4] = offset + 3;
            indices[i + 5] = offset + 0;

            offset += 4;
        }
        m_IndexBuffer = std::make_unique<OpenGLIndexBuffer>(indices, RENDERER_INDICES_SIZE); // TODO: create indices buffer

        OpenGLVertexBufferLayout layout = VertexData::GetLayout();

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

        m_VertexArray->Generate();
        m_VertexBuffer->Generate();
        m_VertexBuffer->BindBufferData();
        m_VertexArray->AddBuffer(*m_VertexBuffer, layout);
        m_IndexBuffer->Generate();
        m_IndexBuffer->BindBufferData();

        delete[] indices; // index buffer now points to trash data

        m_Shader.Generate();
        m_Shader.Bind();
        m_Shader.SetUniformMat4f("u_MVP", glm::mat4(1.0f)); // default MVP matrix - identity matrix

        return true;
    }

    void BatchRenderer2D::ProvideShader(const std::string& filepath) {
        m_Shader = OpenGLShader(filepath);
        m_Shader.Generate();
    }
    void BatchRenderer2D::ProvideShader(const ShaderProgramSource& source) {
        m_Shader = OpenGLShader(source);
        m_Shader.Generate();
    }

    void BatchRenderer2D::Begin() {
        m_VertexArray->Bind();
        m_Buffer = (VertexData*)m_VertexBuffer->MapBuffer(OpenGLBufferAccess::WriteOnly); // map buffer to write data
    }
    void BatchRenderer2D::Submit(const Renderable2D* renderable) {
        const auto& position = renderable->GetPosition();
        const auto& size = renderable->GetSize();
        const auto& color = renderable->GetColor();

        int r = color.r * 255;
        int g = color.g * 255;
        int b = color.b * 255;
        int a = color.a * 255;

        unsigned c = (a << 24) | (b << 16) | (g << 8) | r; // RGBA to unsigned int
        /* Culling might not be uncompatable -- current orientation is ccw, but native OpenGL renders back face */
        glm::vec4 pos1 = (*m_TransformationBack) * glm::vec4(position, 1.0f);
        m_Buffer->position = glm::vec3(pos1.x, pos1.y, pos1.z);
        m_Buffer->color = c;
        m_Buffer++;

        glm::vec4 pos2 = (*m_TransformationBack) * glm::vec4(position.x, position.y + size.y, position.z, 1.0f);
        m_Buffer->position = glm::vec3(pos2.x, pos2.y, pos2.z);
        m_Buffer->color = c;
        m_Buffer++;

        glm::vec4 pos3 = (*m_TransformationBack) * glm::vec4(position.x + size.x, position.y + size.y, position.z, 1.0f);
        m_Buffer->position = glm::vec3(pos3.x, pos3.y, pos3.z);
        m_Buffer->color = c;
        m_Buffer++;

        glm::vec4 pos4 = (*m_TransformationBack) * glm::vec4(position.x + size.x, position.y, position.z, 1.0f);
        m_Buffer->position = glm::vec3(pos4.x, pos4.y, pos4.z);
        m_Buffer->color = c;
        m_Buffer++;

        m_IndexCount += 6; // 6 indices per quad
    }
    void BatchRenderer2D::End() {
        m_VertexArray->Bind();
        m_VertexBuffer->UnmapBuffer();
    }

    void BatchRenderer2D::Flush() {
        m_VertexArray->Bind();
        m_IndexBuffer->Bind();

        m_Shader.Bind();

        // m_VertexBuffer->Bind(); // bind the buffer data to the GPU

        // GLint size;
        // glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);

        // GLvoid* data = malloc(size);
        // glGetBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, size, data);
        // for(int i=0;i<24;i++) {
            
        //     std::cout << ((unsigned int*)data)[i] << ", ";
        // }
        // std::cout << std::endl;

        // // Now you can use the data (do not forget to free it)
        // free(data);
        // std::cin.get();


        glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, nullptr); // draw the elements
        m_IndexCount = 0; // reset index count for next batch
    }
}