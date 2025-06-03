#pragma once
#include "RenderCommand.h"
#include "Camera.h"
#include "Shader.h"

namespace Voyager {

	class Renderer
	{
	public:
		static void BeginScene(Camera& camera);
		static void EndScene();

		static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));

		inline static GraphicsAPI GetAPI() { return RenderCommand::GetAPI(); }
	private:
		struct SceneData { glm::mat4 ViewProjectionMatrix = glm::mat4(1.0f); };
		inline static Scope<SceneData> s_SceneData = CreateScope<Renderer::SceneData>();
	};
}
