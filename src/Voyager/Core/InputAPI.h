#pragma once
#include "pch.h"
#include "Base.h"
#include "GraphicsAPI.h"
#include "KeyCodes.h"
#include "MouseCodes.h"

namespace Voyager {

	class InputAPI
	{
	public:
        InputAPI(void* native_window): m_NativeWindow(native_window) {}
		virtual ~InputAPI() = default;

		virtual bool IsKeyPressed(KeyCode key) = 0;
		virtual bool IsMouseButtonPressed(MouseCode button) = 0;
		virtual glm::vec2 GetMousePosition() = 0;
		virtual float GetMouseX() = 0;
		virtual float GetMouseY() = 0;

		template <API T>
		static Scope<InputAPI> Create(void* native_window);
    protected:
        void* m_NativeWindow;
	};

    template<>
    Scope<InputAPI> InputAPI::Create<API::OpenGL>(void* native_window);

}
