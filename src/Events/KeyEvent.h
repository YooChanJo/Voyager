#pragma once

#include "Event.h"

namespace Voyager {
    class KeyEvent: public Event { // key event category
    public:
        inline int GetKeyCode() const { return m_KeyCode; }

        EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput);    
    protected:
        KeyEvent(Window* window, int keycode): m_KeyCode(keycode), Event(window) {}

        int m_KeyCode;
    };

    class KeyPressedEvent: public KeyEvent { // key pressed event type (repeat)
    public:
        KeyPressedEvent(Window* window, int keycode, int repeatCount): KeyEvent(window, keycode), m_RepeatCount(repeatCount) {}
        
        inline int GetRepeatCount() const { return m_RepeatCount; }

        std::string ToString() const override { // only for debug purposes
            std::stringstream ss;
            ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyPressed)
    private:
        int m_RepeatCount;
    };

    class KeyReleasedEvent: public KeyEvent { // key released event type
    public:
        KeyReleasedEvent(Window* window, int keycode): KeyEvent(window, keycode) {}

        std::string ToString() const override { // only for debug purposes
            std::stringstream ss;
            ss << "KeyReleasedEvent: " << m_KeyCode;
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyReleased)
    };
}



