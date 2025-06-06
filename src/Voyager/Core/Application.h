#pragma once
#include "pch.h"

#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "ImGuiLayer.h"
#include "Window.h"
#include "Timer.h"
#include "Timestep.h"
#include "GraphicsAPI.h"

#include "Renderer/RenderCommand.h"

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

    /* Windows are created to match the api of RenderCommand.h */
    class Application {
    public:
        Application(/* const ApplicationSpecification& specification,  */GraphicsAPI api);
        virtual ~Application();

        void Run();

        inline Timestep GetTimestep() const { return m_Timestep; }
        inline Scope<Window>& GetWindow() { return m_Window; } // get the window at index
        inline static GraphicsAPI GetAPI() { return RenderCommand::s_API; }
        inline static Application& Get() { return *s_Instance; } // get the instance of the app
    protected:
        virtual bool OnWindowClose(const WindowCloseEventPtr& e);
        virtual bool OnWindowResize(const WindowResizeEventPtr& e);
    private:
        void OnEvent(const EventPtr& e);
    private:
        bool m_Running = false;

        Timer m_Timer;
        Timestep m_Timestep; // for deltatime purpose
        float m_LastFrameTime = 0.0f; // tracks last frame time

        Scope<Window> m_Window;
        Scope<ImGuiLayer> m_ImGuiLayer; // the highest overlay handled with priority
        // ApplicationSpecification m_Specification;
        
        inline static Application* s_Instance = nullptr;
    };

    // to be defined in CLIENT
    Application* CreateApplication(ApplicationCommandLineArgs args);
}