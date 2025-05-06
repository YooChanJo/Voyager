// #include "RendererAPI.h"
// #include "API/OpenGL/OpenGLRendererAPI.h"

// namespace Voyager {

// 	template <API T>
// 	Scope<RendererAPI> RendererAPI::Create()
// 	{
// 		if constexpr (T == API::OpenGL) {
// 			return CreateScope<OpenGLRendererAPI>();
// 		}
// 		static_assert(false, "Unsupported API type to create RendererAPI");
// 	}
// 	// template Scope<RendererAPI> RendererAPI::Create<API::OpenGL>(); --> Not necessary
// }