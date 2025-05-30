#include "Application.h"
#include "Input.h"

namespace Voyager {
#define BIND_EVENT_FN(Func) std::bind(&Application::Func, this, std::placeholders::_1)
    
    Application::Application(/* const ApplicationSpecification& specification,  */GraphicsAPI api) {
        VG_CORE_ASSERT(!s_Instance, "Application already exists!");
        VG_CORE_ASSERT(api != GraphicsAPI::None, "Cannot set Application GraphicsAPI to None, must specify api");
        RenderCommand::Init(api); // initialize the render command with the api
        s_Instance = this;
        switch(api) {
			case GraphicsAPI::OpenGL: {
                m_Window = Window::Create<GraphicsAPI::OpenGL>();
                m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

                m_ImGuiLayer = CreateScope<ImGuiLayer>(); // replace with api specific
                m_ImGuiLayer->OnAttach();
				break;
			}
			default: {
				VG_CORE_ASSERT(false, "Cannot create window with API None");
				return;
			}
		}
        Input::Init(api, m_Window->GetNativeWindow());
        // m_Specification = specification;
    }
    Application::~Application() {
        /* Reset Application instance */
        if(s_Instance == this) s_Instance = nullptr; // set instance to nullptr if this is the current instance
        
        /* Detach imgui layer */
        m_ImGuiLayer->OnDetach();

        /* Reset RenderCommand */
        RenderCommand::Shutdown();

        /* Reset Input */
        Input::Shutdown();
    }

    void Application::OnEvent(const EventPtr& e) {
        EventDispatcher dispatcher(e);

        /* Application level events */
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
        dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OnWindowResize));

        m_ImGuiLayer->OnEvent(e);
        if(e->GetHandled()) return;
        for(auto it = m_Window->m_LayerStack.end(); it != m_Window->m_LayerStack.begin(); ) {
            // handles events from back of the layer stack
            (*--it)->OnEvent(e); // Tries to handle event
            if(e->GetHandled()) break; // if the event was handled in the layer then ok
        }
    }

    void Application::Run() {
        m_Running = true;

        while(!m_Window->IsClosed()) {
            RenderCommand::Clear();
            // main thread queue execution
            // layer handling
            {
                for (Scope<Layer>& layer : m_Window->m_LayerStack) layer->OnUpdate();
                // imgui onupdate is empty
            }
            // imgui rendering
            m_ImGuiLayer->Begin();
            {
                // layers on imgui render
                for (Scope<Layer>& layer : m_Window->m_LayerStack) layer->OnImGuiRender();
            }
            m_ImGuiLayer->End();

            m_Window->OnUpdate();
        }
        VG_CORE_INFO("Ending window loop: {0}", m_Window->GetTitle());
        m_Running = false;
    }

    bool Application::OnWindowClose(const WindowCloseEventPtr& e) { return true; } // overridable

    bool Application::OnWindowResize(const WindowResizeEventPtr& e) // overridable
	{
        /* Reset viewport */
        RenderCommand::SetViewport(0, 0, e->GetWidth(), e->GetHeight());
		return false;
	}

}