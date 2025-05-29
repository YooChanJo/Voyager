#pragma once
#include "pch.h"
#include "VertexArray.h"

#include "Core/Base.h"
#include "Core/GraphicsAPI.h"

namespace Voyager {
	/* The Sole template holder of src/Voyager/Renderer/ */
	/* class RendererAPI is a split class from the window class, managing rendering functions */
    /* One static Platform(GraphicsAPI) specific instance is created within RenderCommand */
	class RendererAPI
	{
	public:
		virtual ~RendererAPI() = default;

		virtual void Init() = 0;
		virtual void SetViewport(int x, int y, int width, int height) = 0;
		virtual void SetClearColor(const glm::vec4& color) = 0;
		/* Might want to add clear flags */
		virtual void Clear() = 0;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount = 0) = 0;
		
		// virtual void DrawLines(const Ref<VertexArray>& vertexArray, uint32_t vertexCount) = 0;
		// virtual void SetLineWidth(float width) = 0;

		template <API T>
		static Scope<RendererAPI> Create();
	};

    template<>
    Scope<RendererAPI> RendererAPI::Create<API::OpenGL>();

}
