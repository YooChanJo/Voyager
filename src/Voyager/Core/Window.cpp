#include "Window.h"
#include "API/OpenGL/OpenGLWindow.h"

namespace Voyager {
    Window::~Window() {
        /* Destroying all layers */
        for (auto it = m_LayerStack.begin(); it != m_LayerStack.end(); ++it) {
            (*it)->OnDetach(); // detach the layer from the window
        }
    }
    void Window::PushLayer(Scope<Layer>&& layer) {
        layer->OnAttach();
        m_LayerStack.PushLayer(std::move(layer));
    }
    void Window::PushOverlay(Scope<Layer>&& overlay) {
        overlay->OnAttach();
        m_LayerStack.PushOverlay(std::move(overlay));
    }
    void Window::PopLayer(unsigned int index) {
        if (index < m_LayerStack.GetLayerInsertIndex()) {
            (*(m_LayerStack.begin() + index))->OnDetach();
            m_LayerStack.PopLayer(index);
        }
    }
    void Window::PopOverLay(unsigned int index) {
        if (index >= m_LayerStack.GetLayerInsertIndex()) {
            (*(m_LayerStack.begin() + index))->OnDetach();
            m_LayerStack.PopOverlay(index);
        }
    }

    template<API T>
    void Window::PollEvents() {
        /* Invalid api */
        static_assert(false, "Unsupported API type to create Window");
    }

    template<>
    void Window::PollEvents<API::OpenGL>() {
        OpenGLWindow::PollWindowEvents(); // preventing busy waiting
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