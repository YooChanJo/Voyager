#include "pch.h"
#include "OrthographicCameraController.h"

#include "Core/Input.h"
#include "Core/KeyCodes.h"
#include "Core/Application.h"

namespace Voyager {
#define BIND_CAMERA_CONTROLLER_EVENT_FN(Func) std::bind(&OrthographicCameraController::Func, this, std::placeholders::_1)
#define APPLICATION_TIMESTEP Application::Get().GetTimestep()
#define APPLICATION_WINDOW Application::Get().GetWindow()

	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool mouseOnly, bool rotation)
		: m_AspectRatio(aspectRatio), m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel), m_Rotation(rotation), m_MouseOnly(mouseOnly)
	{
		m_LastMousePosition = { Input::GetMouseX(), Input::GetMouseY() };
	}

	void OrthographicCameraController::OnUpdate() {
		if(!m_MouseOnly && m_FocusByKeyPressed) {
			/* Todo: Add control over which keys to assign */
			if (Input::IsKeyPressed(Key::A)) {
				m_CameraPosition.x -= cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * APPLICATION_TIMESTEP;
				m_CameraPosition.y -= sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * APPLICATION_TIMESTEP;
			} else if (Input::IsKeyPressed(Key::D)) {
				m_CameraPosition.x += cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * APPLICATION_TIMESTEP;
				m_CameraPosition.y += sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * APPLICATION_TIMESTEP;
			}

			if (Input::IsKeyPressed(Key::W)) {
				m_CameraPosition.x += -sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * APPLICATION_TIMESTEP;
				m_CameraPosition.y += cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * APPLICATION_TIMESTEP;
			} else if (Input::IsKeyPressed(Key::S)) {
				m_CameraPosition.x -= -sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * APPLICATION_TIMESTEP;
				m_CameraPosition.y -= cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * APPLICATION_TIMESTEP;
			}

			if (m_Rotation) {
				if (Input::IsKeyPressed(Key::Q)) m_CameraRotation += m_CameraRotationSpeed * APPLICATION_TIMESTEP;
				if (Input::IsKeyPressed(Key::E)) m_CameraRotation -= m_CameraRotationSpeed * APPLICATION_TIMESTEP;

				/* Normalization to 0 ~ 360 */
				if (m_CameraRotation > 180.0f) m_CameraRotation -= 360.0f;
				else if (m_CameraRotation <= -180.0f) m_CameraRotation += 360.0f;

				m_Camera.SetRotation(m_CameraRotation);
			}
			m_Camera.SetPosition(m_CameraPosition);
		}

		glm::vec2 currentMousePos = Input::GetMousePosition();

		if(Input::IsMouseButtonPressed(Mouse::ButtonLeft) && m_FocusByMousePressed) {
			float xOffset = (currentMousePos.x - m_LastMousePosition.x) / APPLICATION_WINDOW->GetWidth() * 2 * m_AspectRatio;
			float yOffset = (m_LastMousePosition.y - currentMousePos.y) / APPLICATION_WINDOW->GetHeight() * 2; // y coordinate flipped
			
			m_CameraPosition.x -= m_CameraTranslationSpeed * (xOffset * cos(glm::radians(m_CameraRotation)) - yOffset * sin(glm::radians(m_CameraRotation)));
			m_CameraPosition.y -= m_CameraTranslationSpeed * (xOffset * sin(glm::radians(m_CameraRotation)) + yOffset * cos(glm::radians(m_CameraRotation)));

			m_Camera.SetPosition(m_CameraPosition);
		}

		m_LastMousePosition = currentMousePos;
		/* Change moving amount by zoom level */
		m_CameraTranslationSpeed = m_ZoomLevel;
	}

	void OrthographicCameraController::OnEvent(const EventPtr& e) {
		EventDispatcher dispatcher(e);

		dispatcher.Dispatch<MouseButtonPressedEvent>([this](const MouseButtonPressedEventPtr& e) -> bool {
			if(e->GetMouseButton() == Mouse::ButtonLeft) {
				m_FocusByMousePressed = true;
			}
			return false;
		});

		dispatcher.Dispatch<MouseButtonReleasedEvent>([this](const MouseButtonReleasedEventPtr& e) -> bool {
			if(e->GetMouseButton() == Mouse::ButtonLeft) {
				m_FocusByMousePressed = false;
			}
			return false;
		});

		dispatcher.Dispatch<KeyPressedEvent>([this](const KeyPressedEventPtr& e) -> bool {
			m_FocusByKeyPressed = true;
			return false;
		});
		dispatcher.Dispatch<KeyReleasedEvent>([this](const KeyReleasedEventPtr& e) -> bool {
			m_FocusByKeyPressed = false;
			return false;
		});

		dispatcher.Dispatch<MouseScrolledEvent>(BIND_CAMERA_CONTROLLER_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_CAMERA_CONTROLLER_EVENT_FN(OrthographicCameraController::OnWindowResized));
	}

	void OrthographicCameraController::OnResize(float width, float height) {
		m_AspectRatio = width / height;
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
	}

    /* Change this into a more sophicsticated mouse controller */
	bool OrthographicCameraController::OnMouseScrolled(const MouseScrolledEventPtr& e) {
		m_ZoomLevel -= e->GetYOffset() * 0.25f;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}

	bool OrthographicCameraController::OnWindowResized(const WindowResizeEventPtr& e) {
		OnResize((float)e->GetWidth(), (float)e->GetHeight());
		return false;
	}

}