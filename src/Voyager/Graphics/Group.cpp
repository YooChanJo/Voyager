#include "Group.h"
// #include "API/OpenGL/Renderers/Renderer2D.h"

namespace Voyager {
    Group::Group(const glm::mat4& transform): m_TransformationMatrix(transform) {}
    void Group::Add(Renderable2D* renderable) {
        m_Renderables.push_back(renderable);
    }

    void Group::Submit(Renderer2D* renderer) const {
        // renderer->Push(m_TransformationMatrix);
        // for(const auto& renderable: m_Renderables) {
        //     renderable->Submit(renderer);
        // }
        // renderer->Pop();
    }
    
}