#pragma once
#include "pch.h"

#include "Base.h"
#include "Events/Event.h"
#include "Layer.h"
#include "LayerStack.h"
#include "GraphicsAPI.h"

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

    class Application;
    
    /* The window class handles innate properties, layer handling */
    /* The window class does not handle rendering functions --> they are handled by the rendererapi */
    /* Direct platform specification is held out in the application class */
    class Window {
        friend class Application;
    protected:
        LayerStack m_LayerStack;
    public: // back to private
        virtual void* GetNativeWindow() const = 0;    
    public:
        using EventCallbackFn = std::function<void(Event&)>;
        virtual ~Window();
    public:
        void PushLayer(Scope<Layer>&& layer);
        void PushOverlay(Scope<Layer>&& overlay);
        void PopLayer(unsigned int index);
        void PopOverLay(unsigned int index);
        inline std::vector<Scope<Layer>>::iterator Find(const std::string& name) { return m_LayerStack.Find(name); } // find layer by name
        inline const LayerStack& GetLayerStack() const { return m_LayerStack; }
        
        /* Defined platform(GraphicsAPI) specific */
        virtual std::string GetTitle() const = 0;
        virtual int GetWidth() const = 0;
        virtual int GetHeight() const = 0;
        // virtual void SetVSync(bool enabled) = 0;
        // virtual bool IsVSync() const = 0;

        virtual void SetTitle(const std::string& title) = 0;
        virtual void SetSize(int width, int height) = 0;
    private:
        virtual void BeforeLoop() = 0; // before the loop starts
        virtual void AfterLoop() = 0; // after the loop ends
        virtual void BeginFrame() = 0; // before the frame starts
        virtual void EndFrame() = 0; // after the frame ends
        
        virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
        virtual bool IsClosed() const = 0;
    public:
        /* Static functions */
        template<API T>
        static void PollEvents(); // never block waiting, just wait for a small moment for blocking busy waiting

        template<API T>
        static Ref<Window> Create(const WindowProps& props = WindowProps());
    };
    template<>
    void Window::PollEvents<API::OpenGL>();
    template<>
    Ref<Window> Window::Create<API::OpenGL>(const WindowProps& props);
}