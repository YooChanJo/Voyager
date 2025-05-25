#include "OpenGLInputAPI.h"

#include <GLFW/glfw3.h>

namespace Voyager {
    bool OpenGLInputAPI::IsKeyPressed(KeyCode key) {
		auto state = glfwGetKey((GLFWwindow*)m_NativeWindow, static_cast<int32_t>(key));
		return state == GLFW_PRESS;
    }
    bool OpenGLInputAPI::IsMouseButtonPressed(MouseCode button) {
		auto state = glfwGetMouseButton((GLFWwindow*)m_NativeWindow, static_cast<int32_t>(button));
		return state == GLFW_PRESS;
    }
    glm::vec2 OpenGLInputAPI::GetMousePosition() {
		double xpos, ypos;
		glfwGetCursorPos((GLFWwindow*)m_NativeWindow, &xpos, &ypos);
        
		return { (float)xpos, (float)ypos };
    }
    float OpenGLInputAPI::GetMouseX() {
		return GetMousePosition().x;
    }
    float OpenGLInputAPI::GetMouseY() {
		return GetMousePosition().y;
    }
}