#pragma once
#include "pch.h"
#include "Core/Base.h"

#define BIT(x) (1 << (x))

namespace Voyager {
    // Currently is blocking events
    // For further improvements, use buffer events in an event bus and process them in the event stage

    enum class EventType {
        None = 0,
        WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
        /* AppTick, AppUpdate, AppRender, */ // currently events are tied to window events
        KeyPressed, KeyReleased,
        MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
    };
    enum EventCategory { // Up to 32 categories + 1(None)
        None = 0,
        EventCategoryApplication    = BIT(0),
        EventCategoryInput          = BIT(1),
        EventCategoryKeyboard       = BIT(2),
        EventCategoryMouse          = BIT(3),
        EventCategoryMouseButton    = BIT(4)
    };

// macros for overiding event derived classes
#define EVENT_CLASS_TYPE(type)  static EventType GetStaticType() { return EventType::type; }\
                                virtual EventType GetEventType() const override { return GetStaticType(); }\
                                virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }
    /* Event being virtual creates error in event buffering */
    class Event {
        friend class EventDispatcher;
    public:
        Event() = default;
        inline virtual EventType GetEventType() const = 0;
        inline virtual const char* GetName() const = 0;
        inline virtual int GetCategoryFlags() const = 0;
        inline virtual std::string ToString() const { return GetName(); };
        
        inline bool IsInCategory(EventCategory category) const {
            return GetCategoryFlags() & category;
        }

        inline bool GetHandled() const { return m_Handled; }
    protected:
        bool m_Handled = false;
    };

    using EventPtr = Ref<Event>; // pointer to the event object
    template <typename T> // T is the type of an Event
    using EventDispatchFn = std::function<bool(const Ref<T>&)>;
    class EventDispatcher // called in each layer each onEvent(EventCallbackFn) to dispatch events
	{
	public:
		EventDispatcher(const EventPtr& event): m_Event(event) {}
		
		template<typename T>
		bool Dispatch(const EventDispatchFn<T>& func)
		{
			if (m_Event->GetEventType() == T::GetStaticType())
			{
				m_Event->m_Handled = func(std::dynamic_pointer_cast<T>(m_Event));
				return true;
			}
			return false;
		}
	private:
		EventPtr m_Event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e) {
		return os << e.ToString();
	}

}

