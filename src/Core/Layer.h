#pragma once

#include "Base.h"
#include "Events/Event.h"

namespace Voyager {
    class Window;
    class Layer {
    public:
        Layer(const std::string& name = "Layer");
        virtual ~Layer() = default;

        virtual void OnAttach(Window* window) {}
        virtual void OnDetach(Window* window) {}
        virtual void OnUpdate(Window* window) {}
        
        /* event.GetWindow() would return pointer to window */
        virtual void OnEvent(Event& event) {}

        inline const std::string& GetName() const { return m_Name; }

        static Scope<Layer> Create(const std::string& name = "Layer");
    private:
        std::string m_Name;
    };
}

