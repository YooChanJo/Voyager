#pragma once
#include "Renderer/OrthographicCamera.h"

#include "Events/ApplicationEvent.h"
#include "Events/MouseEvent.h"
#include "Events/KeyEvent.h"

namespace Voyager {

	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float aspectRatio, bool mouseOnly = false, bool rotation = false);

		void OnUpdate();
		void OnEvent(const EventPtr& e);

		void OnResize(float width, float height);

		inline OrthographicCamera& GetCamera() { return m_Camera; }
		inline const OrthographicCamera& GetCamera() const { return m_Camera; }

		float GetZoomLevel() const { return m_ZoomLevel; }
		void SetZoomLevel(float level) { m_ZoomLevel = level; }
	private:
		bool OnMouseScrolled(const MouseScrolledEventPtr& e);
		bool OnWindowResized(const WindowResizeEventPtr& e);
	private:
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		OrthographicCamera m_Camera;

		bool m_Rotation;
		bool m_MouseOnly;

		glm::vec2 m_LastMousePosition;
		bool m_FocusByMousePressed = false;

		bool m_FocusByKeyPressed = false;

		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_CameraRotation = 0.0f; // In degrees, in the anti-clockwise direction
		float m_CameraTranslationSpeed = 1.0f, m_CameraRotationSpeed = 180.0f;
	};

}