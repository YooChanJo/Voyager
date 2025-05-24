#pragma once
#include "pch.h"

namespace Voyager {
    /* Change this to renderer of global */
    class Renderer2D;

    class Renderable2D {
    protected:
        glm::vec3 m_Position;
        glm::vec2 m_Size;
        glm::vec4 m_Color;  
    protected:
        Renderable2D() = default;  
    public:
        Renderable2D(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
        ~Renderable2D();
        
        virtual void Submit(Renderer2D* renderer) const;
    public:
        inline const glm::vec3& GetPosition() const { return m_Position; }
        inline const glm::vec2& GetSize() const { return m_Size; }
        inline const glm::vec4& GetColor() const { return m_Color; }
    };
}