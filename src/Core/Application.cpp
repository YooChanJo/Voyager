#include "Application.h"

namespace Voyager {
#define BIND_EVENT_FN(Func) std::bind(&Application::Func, this, std::placeholders::_1)
    
    Application::Application(/* const ApplicationSpecification& specification,  */GraphicsAPI api) {
        VG_CORE_ASSERT(!s_Instance, "Application already exists!");
        VG_CORE_ASSERT(api != GraphicsAPI::None, "Cannot set Application GraphicsAPI to None, must specify api");
        RenderCommand::Init(api); // initialize the render command with the api
        s_Instance = this;
        // m_Specification = specification;
    }
    Application::~Application() {
        if(s_Instance == this) s_Instance = nullptr; // set instance to nullptr if this is the current instance
    }

    /* Do this operation only in the main thread */
    void Application::AddWindow(const WindowProps& props) {
        // create a new window and push it to the window registry
        if(m_Running) {
            // change this part to submit method ==> Needs some modification
            VG_CORE_ASSERT(false, "Application is running, cannot use this method");
            return;
        }
        switch(RenderCommand::s_API) {
            case GraphicsAPI::OpenGL: {
                std::scoped_lock<std::mutex> lock1(m_WindowRegistryMutex);
                m_WindowRegistry.push_back(CreateScope<WindowRegistryElement>(Window::Create<GraphicsAPI::OpenGL>(props)));
                m_WindowRegistry.back()->Window->SetEventCallback(BIND_EVENT_FN(OnEvent)); // set event callback for the new window
                m_WindowEventMutexMap[m_WindowRegistry.back()->Window.get()] = CreateScope<std::mutex>(); // requires cleanup;
                break;   
            }
            default: {
                VG_CORE_ASSERT(false, "Cannot create window in application with current GraphicsAPI");
                return;
            }
        }
    }

    void Application::OnEvent(const EventPtr& e) {
        /* Adding events to corresponding window event buffer(queue) */
        std::scoped_lock<std::mutex> lock(*(m_WindowEventMutexMap[e->GetWindow()].get()));
        e->GetWindow()->m_EventQueue.emplace(e);
    }

    void Application::RunWindow(WindowPtr window) {
        window->BeforeLoop();
        while(!window->IsClosed()) {
            window->BeginFrame();

            // main thread queue execution

            // layer handling
            {
                for (Scope<Layer>& layer : window->m_LayerStack) layer->OnUpdate(window.get());
            }
            // would want imgui etc over here

            window->EndFrame();

            /* Handle Buffered Events */
            {
                std::scoped_lock<std::mutex> lock(*(m_WindowEventMutexMap[window.get()].get()));
                // possible want to buffer events at this point and handle them at the event section of the loop
                while(!window->m_EventQueue.empty()) {
                    EventPtr& e = window->m_EventQueue.front();
                    EventDispatcher dispatcher(e);

                    dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
                    dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OnWindowResize));
                    for(auto it = window->m_LayerStack.end(); it != window->m_LayerStack.begin(); ) {
                        // handles events from back of the layer stack
                        (*--it)->OnEvent(e); // Tries to handle event
                        if(e->GetHandled()) break; // if the event was handled in the layer then ok
                    }
                    window->m_EventQueue.pop();
                }
            }
        }
        window->AfterLoop();
        /* Flagging window */
        {
            std::scoped_lock<std::mutex> lock(m_WindowRegistryMutex);
            for (auto it = m_WindowRegistry.begin(); it != m_WindowRegistry.end(); ++it) {
                if (((*it)->Window) == window) {
                    (*it)->RemoveFlag = true;           // Flag the register element for removal
                    break;                           // stop after first match
                }
            }
        }
    }

    void Application::Run() {
        // run the app loop for each window in the registry
        for (auto& element : m_WindowRegistry) {
            const WindowPtr& window = element->Window;
            std::thread thread([this, window]() {
                RunWindow(window);
            });
            thread.detach();            
        }
        m_Running = true;
        while (m_WindowRegistry.size() > 0) {
            /* Handle Events per Loop */
            switch(RenderCommand::s_API) {
                case GraphicsAPI::OpenGL: {
                    Window::PollEvents<GraphicsAPI::OpenGL>();
                    break;
                }
                default: {
                    VG_CORE_ASSERT(false, "Cannot handle events in application with current GraphicsAPI");
                    break;
                }
            }
            /* Destroying Window and Erasing it */
            {
                std::scoped_lock<std::mutex> lock1(m_WindowRegistryMutex);
                for (auto it = m_WindowRegistry.begin(); it != m_WindowRegistry.end(); ) {
                    if ((*it)->RemoveFlag) {
                        /* Child thread is destroyed --> delete mutex */
                        m_WindowEventMutexMap.erase((*it)->Window.get());
                        /* Delete window from map */

                        /* Delete window */
                        it = m_WindowRegistry.erase(it); // erase returns next valid iterator
                    } else {
                        ++it;
                    }
                }
            }
            /* 100 times per second might need adjustments */
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
        m_Running = false;
    }

    bool Application::OnWindowClose(const Ref<WindowCloseEvent>& e) { return true; } // overridable

    bool Application::OnWindowResize(const Ref<WindowResizeEvent>& e) // overridable
	{
        /* Reset viewport */
        RenderCommand::SetViewport(0, 0, e->GetWidth(), e->GetHeight());
		return true;
	}

}