#include "Layer.h"


namespace Voyager {
    Layer::Layer(const std::string& name)
        : m_Name(name) {}
    
    Scope<Layer> Layer::Create(const std::string& name) {
        return CreateScope<Layer>(name);
    }
}