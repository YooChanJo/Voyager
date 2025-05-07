#pragma once
#include "pch.h"

#include <Glad/glad.h>
#include <GLFW/glfw3.h>

#include "Events/Event.h"
#include "Core/Window.h"

namespace Voyager {
    
    /* Does not automatically handle context current */
    class OpenGLWindow: public Window {
    private:
        struct WindowData {
            std::string Title;
            int Width;
            int Height;

            OpenGLWindow* WindowPtr; // pointer to the window object
            bool IsClosed;

            EventCallbackFn EventCallback;
        };

    private:
        GLFWwindow* m_Window;
        WindowData m_Data;
    public:
        OpenGLWindow(const WindowProps& props = WindowProps());
        virtual ~OpenGLWindow();

        /* Util functions --> Move to RendererAPI */
        void MakeWindowContextCurrent() const;
        void SetViewport(int x, int y, int width, int height) const;

        void EnableBlending() const;
        void DisableBlending() const;

        void EnableDepthTest() const;
        void DisableDepthTest() const;

        void EnableCulling() const;
        void DisableCulling() const;

        void SetClearColor(float r, float g, float b, float a) const;
        void Clear() const;
        
        static void PollEventsAndWait(double timeout);

        /* Override functions */
        inline std::string GetTitle() const override { return m_Data.Title; }
        inline int GetWidth() const override { return m_Data.Width; }
        inline int GetHeight() const override { return m_Data.Height; }

        void SetTitle(const std::string& title) override;
        void SetSize(int width, int height) override;
    private:
        inline void* GetNativeWindow() const override { return (void*)m_Window; } // get native window pointer

        void BeforeLoop() override; // before the loop starts
        void AfterLoop() override; // after the loop ends
        void BeginFrame() override; // before the frame starts
        void EndFrame() override; // after the frame ends

        inline bool IsClosed() const override { return m_Data.IsClosed; }
        inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
    private:
        bool Init();
        void ShutDown() const;
    };

}