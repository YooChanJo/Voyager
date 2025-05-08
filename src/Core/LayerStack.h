#pragma once
#include "pch.h"

#include "Base.h"
#include "Layer.h"


namespace Voyager {
    class LayerStack {
    public:
        LayerStack() = default;
        ~LayerStack();

        void PushLayer(Scope<Layer>&& layer); // inserts layers from front(place m_LayerInsert)
        void PushOverlay(Scope<Layer>&& overlay); // inserts overlays from back;
        void PopLayer(unsigned int index);
        void PopOverlay(unsigned int index);

        std::vector<Scope<Layer>>::iterator Find(const std::string& name);

        std::vector<Scope<Layer>>::iterator begin() { return m_Layers.begin(); }
        std::vector<Scope<Layer>>::iterator end() { return m_Layers.end(); }
        std::vector<Scope<Layer>>::reverse_iterator rbegin() { return m_Layers.rbegin(); }
		std::vector<Scope<Layer>>::reverse_iterator rend() { return m_Layers.rend(); }

        inline unsigned int GetLayerInsertIndex() { return m_LayerInsertIndex; }
    private:
        std::vector<Scope<Layer>> m_Layers;
        // The index where overlay begins
        unsigned int m_LayerInsertIndex = 0;
    };
}

