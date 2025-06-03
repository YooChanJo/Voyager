#pragma once
#include "Camera.h"

namespace Voyager {
	/* Orthographic camera is dedicated for 2D scene renderings, for now */
	class OrthographicCamera : public Camera
	{
	public:
		OrthographicCamera(float left, float right, float bottom, float top);

		void SetProjection(float left, float right, float bottom, float top);

		inline void SetPosition(const glm::vec3& position) { m_Position = position; CalculateViewMatrix(); }
		inline void SetRotation(float rotation) { m_Rotation = rotation; CalculateViewMatrix(); }
		
		inline const glm::vec3& GetPosition() const { return m_Position; }
		inline float GetRotation() const { return m_Rotation; }
	private:
		void CalculateViewMatrix();
	private:
		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
		float m_Rotation = 0.0f;
	};

}
