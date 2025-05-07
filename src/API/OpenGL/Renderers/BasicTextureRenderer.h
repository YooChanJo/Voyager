#pragma once

#include "BasicRenderer.h"
#include "API/OpenGL/OpenGLTexture.h"


namespace Voyager {

    class BasicTextureRenderer: public BasicRenderer {
    private:
        OpenGLTexture* m_Texture;
    public:
        BasicTextureRenderer(/* OpenGLWindow& window */);
        ~BasicTextureRenderer();

        void AddTexture(OpenGLTexture& texture, const std::string& name, int slot = 0);

        void Draw() const override;
    };
}
