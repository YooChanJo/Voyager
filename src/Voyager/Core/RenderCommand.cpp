#include "RenderCommand.h"
#include "Application.h"
#include "Assert.h"

namespace Voyager {

	void RenderCommand::Init(GraphicsAPI api) { 
		VG_CORE_ASSERT(!s_RendererAPI, "Static RendererAPI already exists!");
		switch(api) {
			case GraphicsAPI::OpenGL: {
				s_API = api;
				s_RendererAPI = RendererAPI::Create<GraphicsAPI::OpenGL>();
				break;
			}
			default: {
				VG_CORE_ASSERT(false, "Cannot initialize RenderCommand with API None");
				return;
			}
		}
		s_RendererAPI->Init();
	}
}
