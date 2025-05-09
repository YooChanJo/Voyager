#pragma once
#include "pch.h"

#include <Glad/glad.h>
#include <GLFW/glfw3.h>

#include "Events/Event.h"
#include "Core/Window.h"

namespace Voyager {
    /* Creating and deletion only on main thread */
    /* Does not automatically handle context current */
    class OpenGLWindow: public Window {
    private:
        struct WindowData {
            std::string Title;
            int Width;
            int Height;

            OpenGLWindow* CurrentWindow; // pointer to the window object
            bool IsClosed;

            EventCallbackFn EventCallback;
        };

    private:
        GLFWwindow* m_Window;
        WindowData m_Data;
    public:
        OpenGLWindow(const WindowProps& props = WindowProps());
        virtual ~OpenGLWindow();

        // LEGACY Remove make context
        // inline void MakeContextCurrent() const { glfwMakeContextCurrent(m_Window); } // make the window context current

        /* Override functions */
        inline std::string GetTitle() const override { return m_Data.Title; }
        inline int GetWidth() const override { return m_Data.Width; }
        inline int GetHeight() const override { return m_Data.Height; }

        void SetTitle(const std::string& title) override;
        void SetSize(int width, int height) override;
    public:
        inline void* GetNativeWindow() const override { return (void*)m_Window; } // get native window pointer
    private:

        void BeforeLoop() override; // before the loop starts
        void AfterLoop() override; // after the loop ends
        void BeginFrame() override; // before the frame starts
        void EndFrame() override; // after the frame ends

        inline bool IsClosed() const override { return m_Data.IsClosed; }
        inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
    private:
        bool Init();
        void ShutDown() const;
        inline void MakeWindowContextCurrent() const { glfwMakeContextCurrent(m_Window); } // make the window context current
        inline void FreeWindowContextCurrent() const { glfwMakeContextCurrent(nullptr); } // make the window context current
        friend class Window;
        static void PollWindowEvents(); // Window::HandleEvents<API::OpenGL>()
    };

}