#pragma once
#include "pch.h"
#include "Renderable2D.h"


namespace Voyager {
    /* The Group class is derived from Renderable2D, but does not uses size, color, position */
    class Group: Renderable2D {
    private:
        std::vector<Renderable2D*> m_Renderables;
        glm::mat4 m_TransformationMatrix;
    public:
        Group(const glm::mat4& transform);
        void Add(Renderable2D* renderable);

        void Submit(Renderer2D* renderer) const override;
    };

}