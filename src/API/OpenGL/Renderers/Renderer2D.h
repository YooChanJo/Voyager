#pragma once

#include "API/OpenGL/OpenGLWindow.h"
#include "API/OpenGL/OpenGLVertexBufferLayout.h"
#include "API/OpenGL/OpenGLVertexArray.h"
#include "API/OpenGL/OpenGLVertexBuffer.h"
#include "API/OpenGL/OpenGLIndexBuffer.h"
#include "Graphics/Renderable2D.h"

#include "pch.h"

namespace Voyager {        
    
    struct VertexData {
        glm::vec3 position;
        unsigned int color; // 0xAARRGGBB format
        // glm::vec2 texCoord;
        // float texIndex;
        static OpenGLVertexBufferLayout GetLayout();
    };

    class Renderer2D {
    protected:
        OpenGLWindow* m_Window;
        std::vector<glm::mat4> m_TransformationStack;
        const glm::mat4* m_TransformationBack; // cache for debug non inlining
    protected:
        Renderer2D(OpenGLWindow& window);
        virtual ~Renderer2D() = default;
    public:

        void Push(const glm::mat4& matrix, bool override = false);
        void Pop();

        virtual void Submit(Renderable2D* renderable) = 0;
        virtual void Flush() = 0;
    public:
        // virtual void ActivateRenderable(Renderable2D& renderable) const;
    };
}