#pragma once

#include "API/OpenGL/OpenGLWindow.h"
#include "API/OpenGL/OpenGLVertexArray.h"
#include "API/OpenGL/OpenGLVertexBuffer.h"
#include "API/OpenGL/OpenGLVertexBufferLayout.h"
#include "API/OpenGL/OpenGLIndexBuffer.h"
#include "API/OpenGL/OpenGLShader.h"

namespace Voyager {

    class BasicRenderer {
    protected:
        OpenGLWindow* m_Window;
        // All entities are created outside of the renderer, and only passed in as pointers
        OpenGLVertexArray* m_VertexArray;
        OpenGLVertexBuffer* m_VertexBuffer;
        OpenGLVertexBufferLayout* m_Layout;
        OpenGLIndexBuffer* m_IndexBuffer;
        OpenGLShader* m_Shader;
        
    public:
        BasicRenderer(/* OpenGLWindow& window */);
        ~BasicRenderer();
        
        void AddVertexArray(OpenGLVertexArray& vao);
        void AddVertexBufferAndLayout(OpenGLVertexBuffer& vbo, OpenGLVertexBufferLayout& layout);
        void AddIndexBuffer(OpenGLIndexBuffer& ibo);
        void AddShader(OpenGLShader& shader);

        virtual void Draw() const;
    };
}