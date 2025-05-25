#include "Input.h"
#include "Assert.h"

namespace Voyager {

    void Input::Init(GraphicsAPI api, void* native_window) { 
		VG_CORE_ASSERT(!s_InputAPI, "Input instance already exists!");
		switch(api) {
			case GraphicsAPI::OpenGL: {
				s_InputAPI = InputAPI::Create<GraphicsAPI::OpenGL>(native_window);
				break;
			}
			default: {
				VG_CORE_ASSERT(false, "Cannot initialize Input with API None");
				return;
			}
		}
	}
}