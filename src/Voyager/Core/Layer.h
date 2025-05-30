#pragma once

#include "Base.h"
#include "Events/Event.h"

namespace Voyager {
    class Window;
    class Layer {
    public:
        Layer(const std::string& name = "Layer");
        virtual ~Layer() = default;

        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void OnImGuiRender() {}
        virtual void OnUpdate() {}
        
        virtual void OnEvent(const EventPtr& event) {}

        inline const std::string& GetName() const { return m_Name; }
    private:
        std::string m_Name;
    };
}

