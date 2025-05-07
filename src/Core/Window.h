#pragma once
#include "pch.h"

#include "Base.h"
#include "Events/Event.h"
#include "Layer.h"
#include "LayerStack.h"
#include "MapAPI.h"

namespace Voyager {

    struct WindowProps
	{
		std::string Title;
		int Width;
		int Height;

		WindowProps(const std::string& title = "Default Window",
			        int width = 1280,
			        int height = 720)
			: Title(title), Width(width), Height(height)
        {}
	};
    
    class Window {
    protected:
        LayerStack m_LayerStack;
    public:
        using EventCallbackFn = std::function<void(Event&)>;
        virtual ~Window() = default;

        virtual void BeforeLoop() = 0; // before the loop starts
        virtual void AfterLoop() = 0; // after the loop ends
        virtual void BeginFrame() = 0; // before the frame starts
        virtual void EndFrame() = 0; // after the frame ends
        
        virtual void SetEventCallback(const EventCallbackFn& callback) = 0;

        void PushLayer(Ref<Layer> layer);
        void PushOverlay(Ref<Layer> overlay);

        inline LayerStack& GetLayerStack() { return m_LayerStack; }
        
        // virtual int GetWidth() const = 0;
        // virtual int GetHeight() const = 0;
        // virtual void SetVSync(bool enabled) = 0;
        // virtual bool IsVSync() const = 0;

        virtual bool IsClosed() const = 0;
        virtual void* GetNativeWindow() const = 0;

        template<API T>
        static void HandleEvents(); // never block waiting, just wait for a small moment for blocking busy waiting

        template<API T>
        static Ref<Window> Create(const WindowProps& props = WindowProps());
    };
    template<>
    void Window::HandleEvents<API::OpenGL>();

    template<>
    Ref<Window> Window::Create<API::OpenGL>(const WindowProps& props);
}