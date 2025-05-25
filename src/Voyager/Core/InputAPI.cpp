#include "InputAPI.h"
#include "API/OpenGL/OpenGLInputAPI.h"

namespace Voyager {
    template <API T>
	Scope<InputAPI> InputAPI::Create(void* native_window)
	{
		static_assert(false, "Unsupported API type to create InputAPI");
        return nullptr;
	}

    template<>
    Scope<InputAPI> InputAPI::Create<API::OpenGL>(void* native_window) {
        return CreateScope<OpenGLInputAPI>(native_window);
    }
}