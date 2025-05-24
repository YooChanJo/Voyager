#pragma once

#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

#include "Base.h"

namespace Voyager {
    class Log {
    public:
        static void Init();
        
        inline static Ref<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
        inline static Ref<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
    private:
        inline static Ref<spdlog::logger> s_CoreLogger;
        inline static Ref<spdlog::logger> s_ClientLogger;
    };
}

// core log macros
#define VG_CORE_TRACE(...)      ::Voyager::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define VG_CORE_INFO(...)       ::Voyager::Log::GetCoreLogger()->info(__VA_ARGS__)
#define VG_CORE_WARN(...)       ::Voyager::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define VG_CORE_ERROR(...)      ::Voyager::Log::GetCoreLogger()->error(__VA_ARGS__)
#define VG_CORE_CRITICAL(...)   ::Voyager::Log::GetCoreLogger()->critical(__VA_ARGS__)

// client log macros
#define VG_TRACE(...)           ::Voyager::Log::GetClientLogger()->trace(__VA_ARGS__)
#define VG_INFO(...)            ::Voyager::Log::GetClientLogger()->info(__VA_ARGS__)
#define VG_WARN(...)            ::Voyager::Log::GetClientLogger()->warn(__VA_ARGS__)
#define VG_ERROR(...)           ::Voyager::Log::GetClientLogger()->error(__VA_ARGS__)
#define VG_CRITICAL(...)        ::Voyager::Log::GetClientLogger()->critical(__VA_ARGS__)

#define EnableOstreamFormat(Object)  template <> struct fmt::formatter<Object>: fmt::ostream_formatter {};  // Uses operator<<

// Enabling spdlog for all events
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"

EnableOstreamFormat(Voyager::Event)
EnableOstreamFormat(Voyager::WindowCloseEvent)
EnableOstreamFormat(Voyager::WindowResizeEvent)
// EnableOstreamFormat(Voyager::AppTickEvent)
// EnableOstreamFormat(Voyager::AppUpdateEvent)
// EnableOstreamFormat(Voyager::AppRenderEvent)
EnableOstreamFormat(Voyager::KeyPressedEvent)
EnableOstreamFormat(Voyager::KeyReleasedEvent)
EnableOstreamFormat(Voyager::MouseButtonPressedEvent)
EnableOstreamFormat(Voyager::MouseButtonReleasedEvent)
EnableOstreamFormat(Voyager::MouseMovedEvent)
EnableOstreamFormat(Voyager::MouseScrolledEvent)
