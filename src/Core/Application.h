#pragma once

#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Window.h"
#include "MapAPI.h"

#include "Base.h"
#include "Assert.h"

#include "pch.h"

// Might TODO: running more than one instance of app and more than one window per app

namespace Voyager {
    
    struct ApplicationCommandLineArgs
	{
		int Count = 0;
		char** Args = nullptr;

		const char* operator[](int index) const
		{
			VG_CORE_ASSERT(index < Count, "Inappropriate apllication cmd line args specification");
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
        Scope<Window> Window;
        bool RemoveFlag = false;
    };

    class Application {
    public:
        Application(/* const ApplicationSpecification& specification,  */GraphicsAPI api);
        virtual ~Application();

        void Run();

        /* Cannot Add windows during runtime, setup all the windows at the beginning */
        void AddWindow(const WindowProps& props = WindowProps());
        
        inline static GraphicsAPI GetAPI() { return s_API; }
        inline std::vector<WindowRegistryElement>& GetWindowRegistry() { return m_WindowRegistry; }
        
        inline static Application& Get() { return *s_Instance; } // get the instance of the app
    protected:
        virtual bool OnWindowClose(WindowCloseEvent& e);
        // virtual bool OnWindowResize(WindowResizeEvent& e);
        void RunWindow(Window* window);
    private:
        void OnEvent(Event& e);
    private:
        inline static Application* s_Instance = nullptr;
        inline static GraphicsAPI s_API = GraphicsAPI::None;
        
        // ApplicationSpecification m_Specification;
        std::vector<WindowRegistryElement> m_WindowRegistry; // auto memory mangement
    };

    // to be defined in CLIENT
    Application* CreateApplication(ApplicationCommandLineArgs args);
}