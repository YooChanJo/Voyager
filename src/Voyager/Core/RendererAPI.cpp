#include "RendererAPI.h"
#include "API/OpenGL/OpenGLRendererAPI.h"

namespace Voyager {

	template <API T>
	Scope<RendererAPI> RendererAPI::Create()
	{
		static_assert(false, "Unsupported API type to create RendererAPI");
        return nullptr;
	}

    template<>
    Scope<RendererAPI> RendererAPI::Create<API::OpenGL>() {
        return CreateScope<OpenGLRendererAPI>();
    }
}