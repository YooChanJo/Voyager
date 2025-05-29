#include "OpenGLRendererAPI.h"

#include "Core/Log.h"
#include "Core/Assert.h"

#include <Glad/glad.h>

namespace Voyager {
	
	// void OpenGLMessageCallback(
	// 	unsigned source,
	// 	unsigned type,
	// 	unsigned id,
	// 	unsigned severity,
	// 	int length,
	// 	const char* message,
	// 	const void* userParam)
	// {
	// 	switch (severity)
	// 	{
	// 		case GL_DEBUG_SEVERITY_HIGH:         VG_CORE_CRITICAL(message); return;
	// 		case GL_DEBUG_SEVERITY_MEDIUM:       VG_CORE_ERROR(message); return;
	// 		case GL_DEBUG_SEVERITY_LOW:          VG_CORE_WARN(message); return;
	// 		case GL_DEBUG_SEVERITY_NOTIFICATION: VG_CORE_TRACE(message); return;
	// 	}
		
	// 	VG_CORE_ASSERT(false, "Unknown severity level!");
	// }

	void OpenGLRendererAPI::Init()
	{
		// VG_PROFILE_FUNCTION();

	#if 0 // debug mode
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(OpenGLMessageCallback, nullptr);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);
	#endif
    
	}

	void OpenGLRendererAPI::SetViewport(int x, int y, int width, int height) {
		glViewport(x, y, width, height);
	}

	void OpenGLRendererAPI::SetClearColor(const glm::vec4& color) {
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRendererAPI::Clear() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount)
	{
		vertexArray->Bind();
		/* If not specified use the entire index buffer */
		int count = indexCount ? indexCount : vertexArray->GetIndexBuffer()->GetCount();
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
	}

	// void OpenGLRendererAPI::DrawLines(const Ref<VertexArray>& vertexArray, int vertexCount)
	// {
	// 	vertexArray->Bind();
	// 	glDrawArrays(GL_LINES, 0, vertexCount);
	// }

	// void OpenGLRendererAPI::SetLineWidth(float width)
	// {
	// 	glLineWidth(width);
	// }

}
