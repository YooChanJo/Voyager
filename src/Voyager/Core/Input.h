#pragma once
#include "GraphicsAPI.h"
#include "KeyCodes.h"
#include "MouseCodes.h"
#include "InputAPI.h"

#include <glm/glm.hpp>

namespace Voyager {

	class Input
	{
		friend class Application;
	public:
		inline static bool IsKeyPressed(KeyCode key) { return s_InputAPI->IsKeyPressed(key); }
		inline static bool IsMouseButtonPressed(MouseCode button) { return s_InputAPI->IsMouseButtonPressed(button); }
		inline static glm::vec2 GetMousePosition() { return s_InputAPI->GetMousePosition(); }
		inline static float GetMouseX() { return s_InputAPI->GetMouseX(); }
		inline static float GetMouseY() { return s_InputAPI->GetMouseY(); }
	private:
		static void Init(GraphicsAPI api, void* native_window); // only called by class application
		static void Shutdown();
		inline static Scope<InputAPI> s_InputAPI = nullptr;
	};
}
