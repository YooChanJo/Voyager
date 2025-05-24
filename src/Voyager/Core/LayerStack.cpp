#include "LayerStack.h"

namespace Voyager {

    void LayerStack::PushLayer(Scope<Layer>&& layer) {
        m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, std::move(layer));
        m_LayerInsertIndex++;
    }
    void LayerStack::PushOverlay(Scope<Layer>&& overlay) {
        m_Layers.emplace_back(std::move(overlay));
    }
    void LayerStack::PopLayer(unsigned int index) {
        if(m_Layers.size() == 0) return; // no layers to pop
        if (index < m_LayerInsertIndex) {
            m_Layers.erase(this->begin() + index);
            m_LayerInsertIndex--;
        }
    }
    void LayerStack::PopOverlay(unsigned int index) {
        if(m_Layers.size() == 0) return; // no layers to pop
        if (index >= m_LayerInsertIndex) {
            m_Layers.erase(m_Layers.begin() + index);
        }
    }

    std::vector<Scope<Layer>>::iterator LayerStack::Find(const std::string& name) {
        for (auto it = m_Layers.begin(); it != m_Layers.end(); ++it) {
            if ((*it)->GetName() == name) {
                return it; // Return the first match iterator to the found layer
            }
        }
        return m_Layers.end(); // Return end iterator if not found
    }

}