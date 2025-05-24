#pragma once
#include "Event.h"

namespace Voyager {
    class KeyEvent: public Event { // key event category
    public:
        inline int GetKeyCode() const { return m_KeyCode; }

        EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput);    
    protected:
        KeyEvent(int keycode): m_KeyCode(keycode) {}

        int m_KeyCode;
    };
    using KeyEventPtr = Ref<KeyEvent>;

    class KeyPressedEvent: public KeyEvent { // key pressed event type (repeat)
    public:
        KeyPressedEvent(int keycode, int repeatCount): KeyEvent(keycode), m_RepeatCount(repeatCount) {}
        
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
    using KeyPressedEventPtr = Ref<KeyPressedEvent>;

    class KeyReleasedEvent: public KeyEvent { // key released event type
    public:
        KeyReleasedEvent(int keycode): KeyEvent(keycode) {}

        std::string ToString() const override { // only for debug purposes
            std::stringstream ss;
            ss << "KeyReleasedEvent: " << m_KeyCode;
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyReleased)
    };
    using KeyReleasedEventPtr = Ref<KeyReleasedEvent>;
}



