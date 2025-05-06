#pragma once

#include "Events/Event.h"
#include "Base.h"

namespace Voyager {
    class Layer {
    public:
        Layer(const std::string& debugName = "Layer");
        virtual ~Layer() = default;

        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void OnUpdate() {}
        virtual void OnEvent(Event& event) {}

        inline const std::string& GetName() const { return m_DebugName; }

        static Scope<Layer> Create(const std::string& debugName = "Layer");
    private:
        std::string m_DebugName;
    };
}

