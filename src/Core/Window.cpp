#include "Window.h"
#include "API/OpenGL/OpenGLWindow.h"

namespace Voyager {

    void Window::PushLayer(Ref<Layer> layer) {
        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }
    void Window::PushOverlay(Ref<Layer> overlay) {
        m_LayerStack.PushOverlay(overlay);
        overlay->OnAttach();
    }

    template<API T>
    void Window::HandleEvents() {
        /* Invalid api */
        static_assert(false, "Unsupported API type to create Window");
    }

    template<>
    void Window::HandleEvents<API::OpenGL>() {
        OpenGLWindow::PollEventsAndWait(0.01); // preventing busy waiting
    }
    
    template<API T>
    Scope<Window> Window::Create(const WindowProps& props) {
        /* Invalid api */
        static_assert(false, "Unsupported API type to create Window");
        return nullptr;
    }

    template<>
    Scope<Window> Window::Create<API::OpenGL>(const WindowProps& props) {
        return CreateScope<OpenGLWindow>(props);
    }

    
}