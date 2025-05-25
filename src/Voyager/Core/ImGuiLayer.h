#pragma once
#include "Layer.h"

namespace Voyager {

	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		void OnAttach() override; // requires valid opengl context
		void OnDetach() override;
		void OnEvent(const EventPtr& e) override;

        /* OnUpdate is split into two functions to handle layers in between */
		void Begin();
		void End();

		void BlockEvents(bool block) { m_BlockEvents = block; }
		
		void SetDarkThemeColors();

		unsigned int GetActiveWidgetID() const;
	private:
        /* With Block Events enabled would want this and by default to block unwanted mouse and key events */
		bool m_BlockEvents = true;
	};

}
