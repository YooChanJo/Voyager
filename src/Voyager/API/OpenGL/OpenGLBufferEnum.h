#pragma once
#include <Glad/glad.h>
#include <GLFW/glfw3.h>

namespace Voyager {
    
    enum class OpenGLBufferUsage {
        StaticDraw = GL_STATIC_DRAW,
        DynamicDraw = GL_DYNAMIC_DRAW,
        StreamDraw = GL_STREAM_DRAW
    };

    enum class OpenGLBufferAccess {
        ReadOnly = GL_READ_ONLY,
        WriteOnly = GL_WRITE_ONLY,
        ReadWrite = GL_READ_WRITE
    };
}