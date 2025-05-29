#pragma once
#include "Core/GraphicsAPI.h"
#include "RendererAPI.h"

namespace Voyager {
	class Application;
	/* the class RenderCommand.h holds a static renderAPI, holds a static GraphicsAPI, initiated by the class application */
	class RenderCommand
	{
		friend class Application;
	private:
		inline static GraphicsAPI s_API = GraphicsAPI::None; // should be moved to RenderCommand.h
		inline static Scope<RendererAPI> s_RendererAPI = nullptr;
	public:
		/* Wrapper for s_RendererAPI */
		inline static void SetViewport(int x, int y, int width, int height) { s_RendererAPI->SetViewport(x, y, width, height); }
		inline static void SetClearColor(const glm::vec4& color) { s_RendererAPI->SetClearColor(color); }
		// Window automatically clears screen in the beginning of frame
		inline static void Clear() { s_RendererAPI->Clear();}

		inline static void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount = 0) { s_RendererAPI->DrawIndexed(vertexArray, indexCount);}
		// inline static void DrawLines(const Ref<VertexArray>& vertexArray, uint32_t vertexCount) { s_RendererAPI->DrawLines(vertexArray, vertexCount); }
		// inline static void SetLineWidth(float width) { s_RendererAPI->SetLineWidth(width); }

		inline static GraphicsAPI GetAPI() { return s_API; }
	private:
		/* Init() should only be called once by Application constructor */
		static void Init(GraphicsAPI api); // only called by class application
		static void Shutdown();
	};

}
