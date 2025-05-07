#include "LayerStack.h"

namespace Voyager {
  
    LayerStack::~LayerStack() {
        for(Ref<Layer> layer: m_Layers) {
            layer->OnDetach();
        }
    }

    void LayerStack::PushLayer(Ref<Layer> layer) {
        m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);
		    m_LayerInsertIndex++;
    }
    void LayerStack::PushOverlay(Ref<Layer> overlay) {
        m_Layers.emplace_back(overlay);
    }
    void LayerStack::PopLayer(Ref<Layer> layer) {
        auto it = m_Layers.end(); // Default to end if not found
        for (auto iter = m_Layers.begin(); iter != m_Layers.begin() + m_LayerInsertIndex; ++iter) {
            if (*iter == layer) {
                it = iter; // Found the match
                break; // Exit the loop once a match is found
            }
        }
        if (it != m_Layers.begin() + m_LayerInsertIndex)
        {
          layer->OnDetach();
          m_Layers.erase(it);
          m_LayerInsertIndex--;
        }
    }
    void LayerStack::PopOverlay(Ref<Layer> overlay) {
        auto it = m_Layers.end(); // Default to end if not found
        for (auto iter = m_Layers.begin() + m_LayerInsertIndex; iter != m_Layers.end(); ++iter) {
            if (*iter == overlay) {
                it = iter; // Found the match
                break; // Exit the loop once a match is found
            }
        }
        if (it != m_Layers.end())
        {
          overlay->OnDetach();
          m_Layers.erase(it);
        }
    }

}