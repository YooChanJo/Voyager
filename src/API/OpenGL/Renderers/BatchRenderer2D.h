#pragma once
#include "pch.h"
#include "Renderer2D.h"

namespace Voyager {

    class BatchRenderer2D : public Renderer2D {
    public:
        static constexpr int RENDERER_MAX_SPRITES = 500000;
        static constexpr int RENDERER_VERTEX_SIZE = sizeof(VertexData);
        static constexpr int RENDERER_SPRITE_SIZE = RENDERER_VERTEX_SIZE * 4;
        static constexpr int RENDERER_BUFFER_SIZE = RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES;
        static constexpr int RENDERER_INDICES_SIZE = RENDERER_MAX_SPRITES * 6;

    private:
        std::unique_ptr<OpenGLVertexArray> m_VertexArray;
        std::unique_ptr<OpenGLVertexBuffer> m_VertexBuffer;
        std::unique_ptr<OpenGLIndexBuffer> m_IndexBuffer;
        std::unique_ptr<OpenGLVertexBufferLayout> m_VertexBufferLayout;

        OpenGLShader m_Shader;

        unsigned int m_IndexCount = 0;

        // this pointer is going to be retrieving and writing data to the GPU buffer
        VertexData* m_Buffer;


    public:
        BatchRenderer2D(/* OpenGLWindow& window */);
        ~BatchRenderer2D();

        void ProvideShader(const std::string& filepath);
        void ProvideShader(const ShaderProgramSource& source);
        
        void Begin();
        void Submit(Renderable2D* renderable) override;
        void End();
        void Flush() override;

        inline OpenGLShader& GetShader() { return m_Shader; }
    private:
        bool Init();
    };
}