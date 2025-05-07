#pragma once
#include "pch.h"

namespace Voyager {
        
    class OpenGLTexture {
    private:
        unsigned int m_RendererID;
        std::string m_FilePath;
        unsigned char* m_LocalBuffer;
        int m_Width, m_Height, m_BPP;

        public:
        OpenGLTexture(const std::string& filepath);
        ~OpenGLTexture();

        // called by the renderer --> needs context current
        void Generate();
        void Bind(unsigned int slot = 0) const;
        void Unbind() const;

        inline int GetWidth() const { return m_Width; }
        inline int GetHeight() const { return m_Height; }
        inline int GetBPP() const { return m_BPP; }
    };

}
