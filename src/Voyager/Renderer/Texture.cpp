// #include "hzpch.h"
// #include "Hazel/Renderer/Texture.h"

// #include "Hazel/Renderer/Renderer.h"
// #include "Platform/OpenGL/OpenGLTexture.h"

// namespace Hazel {

// 	Ref<Texture2D> Texture2D::Create(const TextureSpecification& specification)
// 	{
// 		switch (Renderer::GetAPI())
// 		{
// 			case RendererAPI::API::None:    HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
// 			case RendererAPI::API::OpenGL:  return CreateRef<OpenGLTexture2D>(specification);
// 		}

// 		HZ_CORE_ASSERT(false, "Unknown RendererAPI!");
// 		return nullptr;
// 	}

// 	Ref<Texture2D> Texture2D::Create(const std::string& path)
// 	{
// 		switch (Renderer::GetAPI())
// 		{
// 			case RendererAPI::API::None:    HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
// 			case RendererAPI::API::OpenGL:  return CreateRef<OpenGLTexture2D>(path);
// 		}

// 		HZ_CORE_ASSERT(false, "Unknown RendererAPI!");
// 		return nullptr;
// 	}

// }
