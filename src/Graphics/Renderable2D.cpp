#include "Renderable2D.h"
/* Change this to renderer of global */
#include "API/OpenGL/Renderers/Renderer2D.h"

namespace Voyager {
    Renderable2D::Renderable2D(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
        : m_Position(position), m_Size(size), m_Color(color)
    {}
    Renderable2D::~Renderable2D() {}

    void Renderable2D::Submit(Renderer2D* renderer) const {
        renderer->Submit(this);
    }
}