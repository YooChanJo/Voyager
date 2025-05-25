#include "Core/InputAPI.h"

namespace Voyager {
    class OpenGLInputAPI : public InputAPI {
    public:
        OpenGLInputAPI(void* native_window): InputAPI(native_window) {}
        
        virtual bool IsKeyPressed(KeyCode key) override;
		virtual bool IsMouseButtonPressed(MouseCode button) override;
		virtual glm::vec2 GetMousePosition() override;
		virtual float GetMouseX() override;
		virtual float GetMouseY() override;
    };
}