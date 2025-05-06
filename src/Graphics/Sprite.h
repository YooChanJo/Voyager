#pragma once
#include "Renderable2D.h"

namespace Voyager {
    // Sprites sit on the xy plane
    class Sprite: public Renderable2D {
    
    public:
        Sprite(float x, float y, float width, float height, const glm::vec4& color);

        ~Sprite() {}

    };
}