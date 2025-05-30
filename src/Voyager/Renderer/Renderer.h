#pragma once
#include "RenderCommand.h"
#include "Shader.h"

// #include "Hazel/Renderer/OrthographicCamera.h"

namespace Voyager {

	class Renderer
	{
	public:
		// static void Init();
		// static void Shutdown();
		
		// static void OnWindowResize(uint32_t width, uint32_t height);

		static void BeginScene(/* OrthographicCamera& camera */);
		static void EndScene();

		static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));

		inline static GraphicsAPI GetAPI() { return RenderCommand::GetAPI(); }
	private:
		struct SceneData { glm::mat4 ViewProjectionMatrix; };
		inline static Scope<SceneData> s_SceneData = CreateScope<Renderer::SceneData>();
	};
}
