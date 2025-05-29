#include "Renderer/Buffer.h"
#include "Renderer/Renderer.h"

#include "API/OpenGL/OpenGLBuffer.h"

namespace Voyager {

	Ref<VertexBuffer> VertexBuffer::Create(uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case GraphicsAPI::None:    VG_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case GraphicsAPI::OpenGL:  return CreateRef<OpenGLVertexBuffer>(size);
		}

		VG_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case GraphicsAPI::None:    VG_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case GraphicsAPI::OpenGL:  return CreateRef<OpenGLVertexBuffer>(vertices, size);
		}

		VG_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case GraphicsAPI::None:    VG_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case GraphicsAPI::OpenGL:  return CreateRef<OpenGLIndexBuffer>(indices, size);
		}

		VG_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}