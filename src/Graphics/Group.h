#pragma once

#include "Renderable2D.h"

#include "pch.h"

namespace Voyager {

    class Group {
    private:
        std::vector<Renderable2D*> m_Renderables;
        glm::mat4 m_TransformationMatrix;
    public:
        Group();

    };

}