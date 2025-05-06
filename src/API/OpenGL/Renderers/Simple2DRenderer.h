#pragma once

#include "Renderer2D.h"
#include "API/OpenGL/OpenGLShader.h"

#include "pch.h"


namespace Voyager {

    // not for practical use, deprecated, only for debug purposes
    class Simple2DRenderer: public Renderer2D {
    private:
        std::deque<Renderable2D*> m_RenderQueue;
        OpenGLShader m_Shader;
    public:
        Simple2DRenderer(OpenGLWindow& window);
        ~Simple2DRenderer();

        bool Init();

        void ProvideShader(const std::string& filepath);
        void ProvideShader(const ShaderProgramSource& source);
        
        void Submit(Renderable2D* renderable) override;
        void Flush() override; // very very costly and slow, only for debug purposes

        inline OpenGLShader& GetShader() { return m_Shader; }
    };

}
