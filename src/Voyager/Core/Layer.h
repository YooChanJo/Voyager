#pragma once
#include "Timestep.h"
#include "Base.h"
#include "Events/Event.h"

namespace Voyager {
    class Layer {
    public:
        Layer(const std::string& name = "Layer");
        virtual ~Layer() = default;

        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void OnImGuiRender() {}
        virtual void OnUpdate(Timestep ts) {}
        
        virtual void OnEvent(const EventPtr& event) {}

        inline const std::string& GetName() const { return m_Name; }
    private:
        std::string m_Name;
    };
}

