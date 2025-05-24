#pragma once
#include "Event.h"

namespace Voyager {
    class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(unsigned int width, unsigned int height)
			: m_Width(width), m_Height(height)
		{}
		unsigned int GetWidth() const { return m_Width; }
		unsigned int GetHeight() const { return m_Height; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
			return ss.str();
		}

		EVENT_CLASS_CATEGORY(EventCategoryApplication)
		EVENT_CLASS_TYPE(WindowResize)
	private:
		unsigned int m_Width, m_Height;
	};
	using WindowResizeEventPtr = Ref<WindowResizeEvent>;

	class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() = default;
        
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
		EVENT_CLASS_TYPE(WindowClose)
	};
	using WindowCloseEventPtr = Ref<WindowCloseEvent>;

	// class AppTickEvent : public Event
	// {
	// public:
	// 	AppTickEvent() {};

	// 	EVENT_CLASS_CATEGORY(EventCategoryApplication)
	// 	EVENT_CLASS_TYPE(AppTick)
	// };

	// class AppUpdateEvent : public Event
	// {
	// public:
	// 	AppUpdateEvent() {};

	// 	EVENT_CLASS_CATEGORY(EventCategoryApplication)
	// 	EVENT_CLASS_TYPE(AppUpdate)
	// };

	// class AppRenderEvent : public Event
	// {
	// public:
	// 	AppRenderEvent() {};

	// 	EVENT_CLASS_CATEGORY(EventCategoryApplication)
	// 	EVENT_CLASS_TYPE(AppRender)
	// };

}
