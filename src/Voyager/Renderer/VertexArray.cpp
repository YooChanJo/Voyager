#include "pch.h"
#include "VertexArray.h"
#include "Renderer.h"

#include "Core/Assert.h"

#include "API/OpenGL/OpenGLVertexArray.h"

namespace Voyager {

	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
			case GraphicsAPI::None:    VG_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case GraphicsAPI::OpenGL:  return CreateRef<OpenGLVertexArray>();
		}

		VG_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}