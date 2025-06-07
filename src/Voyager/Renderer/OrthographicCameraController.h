#pragma once
#include "Renderer/OrthographicCamera.h"

#include "Events/ApplicationEvent.h"
#include "Events/MouseEvent.h"
#include "Events/KeyEvent.h"

namespace Voyager {

	struct OrthographicCameraControllerOptions {
		bool EnableRotation;
		bool MouseCenteredZoom;
		bool MouseOnly;

		/* Might want to add key control options */
		
		/* TODO: Change this manual bool input into a flag system */
		OrthographicCameraControllerOptions(
			bool enableRotation = false,
			bool mouseCenteredZoom = false,
			bool mouseOnly = false
		) : EnableRotation(enableRotation), MouseCenteredZoom(mouseCenteredZoom), MouseOnly(mouseOnly)
		{}
	};

	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float aspectRatio, OrthographicCameraControllerOptions options = OrthographicCameraControllerOptions());

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

		glm::vec3 ScreenToNDC(const glm::vec2& screenCoord);
	private:
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		OrthographicCamera m_Camera;

		OrthographicCameraControllerOptions  m_Options;

		glm::vec2 m_LastMousePosition;
		/* To only handle events when event is passed on */
		bool m_FocusByMousePressed = false;
		bool m_FocusByKeyPressed = false;

		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_CameraRotation = 0.0f; // In degrees, in the anti-clockwise direction
		float m_CameraTranslationSpeed = 1.0f, m_CameraRotationSpeed = 180.0f;
	};

}