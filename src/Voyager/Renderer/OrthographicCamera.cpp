#include "pch.h"
#include "OrthographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Voyager {

	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
		: Camera(glm::ortho(left, right, bottom, top, -1.0f, 1.0f))
	{
		CalculateViewProjectionMatrix();
	}

	void OrthographicCamera::SetProjection(float left, float right, float bottom, float top) {
		m_ProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
		CalculateViewProjectionMatrix();
	}

	void OrthographicCamera::CalculateViewMatrix() {
		// Considering object rotation first --> then translation
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) * glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));

		// Actual movement is inverse --> translation first then rotation
		m_ViewMatrix = glm::inverse(transform);
		CalculateViewProjectionMatrix();
	}

}