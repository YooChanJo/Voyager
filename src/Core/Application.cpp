#include "Application.h"
#include "Events/ApplicationEvent.h"
#include "Log.h"

#include <thread>
#include <mutex>

namespace Voyager {
#define BIND_EVENT_FN(Func) std::bind(&Application::Func, this, std::placeholders::_1)

   
    static std::mutex s_AppCloseMutex; // mutex for thread safety
    
    Application::Application(/* const ApplicationSpecification& specification,  */GraphicsAPI api) {
        VG_CORE_ASSERT(!s_Instance, "Application already exists!");
        VG_CORE_ASSERT(api != GraphicsAPI::None, "Cannot set Application GraphicsAPI to None, must specify api");
        s_API = api;
		s_Instance = this;
        // m_Specification = specification;
    }
    Application::~Application() {
        if(s_Instance == this) s_Instance = nullptr; // set instance to nullptr if this is the current instance
    }

    /* Cannot Add windows during runtime, setup all the windows at the beginning */
    void Application::AddWindow(const WindowProps& props) {
        // create a new window and push it to the window registry
        switch(s_API) {
            case GraphicsAPI::OpenGL: {
                std::scoped_lock<std::mutex> lock(s_AppCloseMutex); // lock the mutex for thread safety
                m_WindowRegistry.push_back({ Window::Create<GraphicsAPI::OpenGL>(props) });
                m_WindowRegistry.back().Window->SetEventCallback(BIND_EVENT_FN(OnEvent)); // set event callback for the new window
                break;   
            }
            default: {
                VG_CORE_ASSERT(false, "Cannot create window in application with current GraphicsAPI");
                break;
            }
        }
    }

    void Application::OnEvent(Event& e) {
        // possible want to buffer events at this point and handle them at the event section of the loop
        EventDispatcher dispatcher(e);

        // we call event handling functions bool<Event&> and call dispatch
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
        // JK_CORE_TRACE(e);

        for(auto it = e.GetWindow()->GetLayerStack().end(); it != e.GetWindow()->GetLayerStack().begin(); ) {
            // handles events from back of the layer stack
            (*--it)->OnEvent(e); // Tries to handle event
            if(e.GetHandled()) break; // if the event was handled in the layer then ok
        }
    }

    void Application::RunWindow(Ref<Window> window) {
        window->BeforeLoop();
        while(!window->IsClosed()) {
            window->BeginFrame();

            // main thread queue execution

            // layer handling
            {
                for (Ref<Layer> layer : window->GetLayerStack()) layer->OnUpdate();
            }
            // would want imgui etc over here

            window->EndFrame();
        }
        window->AfterLoop();
        /* Flagging window */
        {
            std::scoped_lock<std::mutex> lock(s_AppCloseMutex); // lock the mutex for thread safety
            for (auto it = m_WindowRegistry.begin(); it != m_WindowRegistry.end(); ++it) {
                if ((it->Window) == window) {
                    it->RemoveFlag = true;           // Flag the register element for removal
                    break;                           // stop after first match
                }
            }
        }
    }

    void Application::Run() {
        // run the app loop for each window in the registry
        for (auto& element : m_WindowRegistry) {
            Ref<Window> window = element.Window;
            std::thread thread([this, window]() {
                RunWindow(window);
            });
            thread.detach();            
        }
        while (m_WindowRegistry.size() > 0) {
            /* Handle Events per Loop */
            switch(s_API) {
                case GraphicsAPI::OpenGL: {
                    Window::HandleEvents<GraphicsAPI::OpenGL>();
                    break;
                }
                default: {
                    VG_CORE_ASSERT(false, "Cannot handle events in application with current GraphicsAPI");
                    break;
                }
            }
            /* Destroying Window and Erasing it */
            {
                std::scoped_lock<std::mutex> lock(s_AppCloseMutex); // lock the mutex for thread safety
                for (auto it = m_WindowRegistry.begin(); it != m_WindowRegistry.end(); ) {
                    if (it->RemoveFlag) {
                        it = m_WindowRegistry.erase(it); // erase returns next valid iterator
                    } else {
                        ++it;
                    }
                }
            }
        }
    }

    bool Application::OnWindowClose(WindowCloseEvent& e) { return true; } // overridable

    // bool Application::OnWindowResize(WindowResizeEvent& e) // overridable
	// {
	// 	// if (e.GetWidth() == 0 || e.GetHeight() == 0)
	// 	// {
	// 	// 	m_Minimized = true;
	// 	// 	return false;
	// 	// }

	// 	// m_Minimized = false;
	// 	// if(T == API::OpenGL) e.GetWindow()->SetViewport(0, 0, e.GetWidth(), e.GetHeight()); // set viewport to window size

	// 	return false;
	// }

}