#pragma once
#include "pch.h"

#include "Base.h"
#include "Layer.h"


namespace Voyager {
    class LayerStack {
    public:
        LayerStack() = default;
        ~LayerStack();

        void PushLayer(Ref<Layer> layer); // inserts layers from front(place m_LayerInsert)
        void PushOverlay(Ref<Layer> overlay); // inserts overlays from back;
        void PopLayer(Ref<Layer> layer);
        void PopOverlay(Ref<Layer> overlay);

        std::vector<Ref<Layer>>::iterator begin() { return m_Layers.begin(); }
        std::vector<Ref<Layer>>::iterator end() { return m_Layers.end(); }
        std::vector<Ref<Layer>>::reverse_iterator rbegin() { return m_Layers.rbegin(); }
		std::vector<Ref<Layer>>::reverse_iterator rend() { return m_Layers.rend(); }
    private:
        std::vector<Ref<Layer>> m_Layers;
        unsigned int m_LayerInsertIndex = 0;
    };
}

