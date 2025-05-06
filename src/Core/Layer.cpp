#include "Layer.h"


namespace Voyager {
    Layer::Layer(const std::string& debugName)
        : m_DebugName(debugName) {}
    
    Scope<Layer> Layer::Create(const std::string& debugName) {
        return CreateScope<Layer>(debugName);
    }
}