#pragma once
#include <glm/glm.hpp>

namespace Voyager {

	class Camera
	{
	public:
		Camera(const glm::mat4& projection = glm::mat4(1.0f), const glm::mat4& view = glm::mat4(1.0f))
			: m_ProjectionMatrix(projection), m_ViewMatrix(view)
		{
			CalculateViewProjectionMatrix();
		}

		virtual ~Camera() = default;

		inline const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		inline const glm::mat4& GetViewionMatrix() const { return m_ViewMatrix; }
		inline const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }
	protected:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix; // for faster computation

		inline void CalculateViewProjectionMatrix() { m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix; }
	};

}