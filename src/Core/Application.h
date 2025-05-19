#pragma once
#include "pch.h"

#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Window.h"
#include "GraphicsAPI.h"
#include "RenderCommand.h"

#include "Base.h"
#include "Assert.h"

#include <thread>
#include <mutex>


// Might TODO: running more than one instance of app and more than one window per app

namespace Voyager {
    
    struct ApplicationCommandLineArgs
	{
		int Count = 0;
		char** Args = nullptr;

		const char* operator[](int index) const
		{
			VG_CORE_ASSERT(index < Count, "Inappropriate application cmd line args specification");
			return Args[index];
		}
	};

	struct ApplicationSpecification
	{
        std::string Name = "Default Application";
		std::string WorkingDirectory;
		ApplicationCommandLineArgs CommandLineArgs;
	};

    struct WindowRegistryElement
    {
        WindowPtr Window;
        bool RemoveFlag;
        WindowRegistryElement(WindowPtr window, bool removeflag = false): Window(window), RemoveFlag(removeflag) {}
    };

    /* Windows are created to match the api of RenderCommand.h */
    class Application {
    public:
        Application(/* const ApplicationSpecification& specification,  */GraphicsAPI api);
        virtual ~Application();

        void Run();

        /* Only add in the main thread */
        void AddWindow(const WindowProps& props = WindowProps());
        inline WindowPtr GetWindow(unsigned int index) { return m_WindowRegistry[index]->Window; } // get the window at index
        
        inline static GraphicsAPI GetAPI() { return RenderCommand::s_API; }
        inline const std::vector<Scope<WindowRegistryElement>>& GetWindowRegistry() const { return m_WindowRegistry; }
        
        inline static Application& Get() { return *s_Instance; } // get the instance of the app
    protected:
        virtual bool OnWindowClose(const Ref<WindowCloseEvent>& e);
        virtual bool OnWindowResize(const Ref<WindowResizeEvent>& e);
    private:
        void RunWindow(WindowPtr window);
        void OnEvent(const EventPtr& e);
    private:
        bool m_Running = false;
        inline static Application* s_Instance = nullptr;
        // ApplicationSpecification m_Specification;

        std::vector<Scope<WindowRegistryElement>> m_WindowRegistry; // auto memory mangement
        /* Only the thread of window and the main thread access these mutex --> Called independently alone to prevent deadlock */
        /* Locks the window event queue */
        std::unordered_map<Window*, Scope<std::mutex>> m_WindowEventMutexMap; // event mutex for each window

        /* Mutex lock order */
        std::mutex m_WindowRegistryMutex; // used when modifying window registry and its elements
    };

    // to be defined in CLIENT
    Application* CreateApplication(ApplicationCommandLineArgs args);
}