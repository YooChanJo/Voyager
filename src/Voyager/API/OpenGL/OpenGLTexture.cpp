// OpenGL
#include <Glad/glad.h>
#include <stb_image/stb_image.h>

#include "OpenGLTexture.h"
#include "Core/Log.h"

namespace Voyager {
        
    OpenGLTexture::OpenGLTexture(const std::string& filepath)
        : m_RendererID(0), m_FilePath(filepath), m_LocalBuffer(nullptr), m_Width(0), m_Height(0), m_BPP(0)
    {
        stbi_set_flip_vertically_on_load(1);
        m_LocalBuffer = stbi_load(filepath.c_str(), &m_Width, &m_Height, &m_BPP, 4);

        if (!m_LocalBuffer) {
            VG_CORE_ERROR("Failed to load texture at path: {0}", filepath);
        }
    }
    OpenGLTexture::~OpenGLTexture() {
        if(m_RendererID != 0) glDeleteTextures(1, &m_RendererID);
    }

    void OpenGLTexture::Generate() {
        if(m_RendererID != 0) return;
        glGenTextures(1, &m_RendererID);
        glBindTexture(GL_TEXTURE_2D, m_RendererID);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer);
        glBindTexture(GL_TEXTURE_2D, 0);

        if(m_LocalBuffer) { // free memory
            stbi_image_free(m_LocalBuffer);
        }
    }

    void OpenGLTexture::Bind(unsigned int slot) const {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, m_RendererID);
    }
    void OpenGLTexture::Unbind() const {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}
