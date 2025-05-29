#include "RenderCommand.h"
#include "Core/Application.h"
#include "Core/Assert.h"

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
	void RenderCommand::Shutdown() {
		RenderCommand::s_API = GraphicsAPI::None; // should be moved to RenderCommand.h
		RenderCommand::s_RendererAPI = nullptr;
	}
}
