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
        Ref<Window> Window;
        bool RemoveFlag = false;
    };

    /* Windows are created to match the api of RenderCommand.h */
    class Application {
    public:
        Application(/* const ApplicationSpecification& specification,  */GraphicsAPI api);
        virtual ~Application();

        void Run();

        /* Cannot Add windows during runtime, setup all the windows at the beginning */
        void AddWindow(const WindowProps& props = WindowProps());
        inline Ref<Window> GetWindow(unsigned int index) { return m_WindowRegistry[index].Window; } // get the window at index
        
        inline static GraphicsAPI GetAPI() { return RenderCommand::s_API; }
        inline const std::vector<WindowRegistryElement>& GetWindowRegistry() const { return m_WindowRegistry; }
        
        inline static Application& Get() { return *s_Instance; } // get the instance of the app
    protected:
        virtual bool OnWindowClose(const Ref<WindowCloseEvent>& e);
        // virtual bool OnWindowResize(WindowResizeEvent& e);
        void RunWindow(Ref<Window> window);
    private:
        void OnEvent(const EventPtr& e);
    private:
        inline static Application* s_Instance = nullptr;
        
        // ApplicationSpecification m_Specification;
        std::vector<WindowRegistryElement> m_WindowRegistry; // auto memory mangement
        /* Only the thread of window and the main thread access these mutex --> Called independently alone to prevent deadlock */
        /* Locks the window event queue */
        std::unordered_map<Window*, Scope<std::mutex>> m_WindowEventMutexMap; // event mutex for each window

        /* Mutex lock order */
        std::mutex m_WindowRegistryMutex;
        std::mutex m_WindowEventMutexMapMutex;
    };

    // to be defined in CLIENT
    Application* CreateApplication(ApplicationCommandLineArgs args);
}