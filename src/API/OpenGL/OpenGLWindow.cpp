#include "OpenGLWindow.h"

#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"

#include "Core/Assert.h"
#include "Core/Log.h"

namespace Voyager {

    static bool s_GLFWInitialized = false;
    static bool s_GladInitialized = false;
    static short s_WindowCount = 0; // number of windows created

    static void GLFWErrorCallback(int error, const char* description) {
        VG_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
    }
    
    OpenGLWindow::OpenGLWindow(const WindowProps& props)
    {
        m_Data.Title = props.Title;
        m_Data.Width = props.Width;
        m_Data.Height = props.Height;
        m_Data.EventCallback = [](Event&){};

        m_Data.WindowPtr = this; // set window pointer to this instance
        VG_CORE_INFO("Creating window {0} ({1}, {2})", m_Data.Title, m_Data.Width, m_Data.Height);
    
        // initialize window data first
        bool success = Init();
        VG_ASSERT(success, "Failed to create and initialize window {0} in class Window", m_Data.Title);
        m_Data.IsClosed = false;
        s_WindowCount++; // increment window count
    }
    
    OpenGLWindow::~OpenGLWindow() { 
        ShutDown(); // shut down the window
    }
    
    void OpenGLWindow::ShutDown() const {
        std::cout << "Destroying window " << m_Window << std::endl;
        glfwDestroyWindow(m_Window);     // destroys window
        std::cout << "Destroyed " << m_Window << std::endl;
        {
            // thread safety
            s_WindowCount--; // decrement window count
            if(s_WindowCount == 0) {
                glfwTerminate(); // terminate glfw
                s_GLFWInitialized = false; // reset s_GLFWInitialized
                s_GladInitialized = false; // reset s_GladInitialized
            }
        }
    }

    bool OpenGLWindow::Init() {
        /* GLFW initialization */
        {
            if(!s_GLFWInitialized) {
                int success = glfwInit();
                VG_CORE_ASSERT(success, "Could not initialize GLFW!");
                glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
                glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
                glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // needs a vao
                s_GLFWInitialized = true;
            }
        }

        /* Window creation */
        m_Window = glfwCreateWindow(m_Data.Width, m_Data.Height, m_Data.Title.c_str(), NULL, NULL);
        if(!m_Window) {
            VG_CORE_ERROR("Failed to create window {0}", m_Data.Title);
            return false;
        }
        glfwSetWindowUserPointer(m_Window, &m_Data); // set m_Data pointer as a data in window
        glfwMakeContextCurrent(m_Window); // set current context to this window

        /* Glad initialization */
        {
            if(!s_GladInitialized) {
                int success = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
                VG_CORE_ASSERT(success, "Failed to initialize glad");
                s_GladInitialized = true;
            }
        }
        /* Enable blending */
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        /* Enable depth test */
		glEnable(GL_DEPTH_TEST); // enable depth test
        glDepthFunc(GL_LESS); // depth test function

        // /* Enable culling face */
        // glEnable(GL_CULL_FACE); // enable culling
        // glCullFace(GL_FRONT); // cull back faces

        /* Enable line smooth */
		// glEnable(GL_LINE_SMOOTH); --> Legacy

        /* Set default viewport */
        glViewport(0, 0, m_Data.Width, m_Data.Height); // set viewport to window size

        /* Set window callback functions --> Only changes window data by default */
        glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window){
            WindowData& data = *reinterpret_cast<WindowData*>(glfwGetWindowUserPointer(window));
            data.IsClosed = true; // set window closed to true

            WindowCloseEvent event(data.WindowPtr);
            data.EventCallback(event);
        });
        glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
            WindowData& data = *reinterpret_cast<WindowData*>(glfwGetWindowUserPointer(window));
            data.Width = width;
            data.Height = height; // modifies all instances of m_Data
            
            WindowResizeEvent event(data.WindowPtr, width, height);
            // would want to reset viewport
            data.EventCallback(event); // calling the callback function 
        });

        glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
            WindowData& data = *reinterpret_cast<WindowData*>(glfwGetWindowUserPointer(window));

            // implement own key code in future
            switch (action) {
                case GLFW_PRESS: {
                    KeyPressedEvent event(data.WindowPtr, key, 0);
                    data.EventCallback(event); // calling the callback function 
                    break;
                }
                case GLFW_RELEASE: {
                    KeyReleasedEvent event(data.WindowPtr, key);
                    data.EventCallback(event); // calling the callback function 
                    break;
                }
                case GLFW_REPEAT: {
                    KeyPressedEvent event(data.WindowPtr, key, 1);
                    data.EventCallback(event); // calling the callback function 
                    break;
                }
            }
        });
        glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) {
            WindowData& data = *reinterpret_cast<WindowData*>(glfwGetWindowUserPointer(window));

            switch (action) {
                case GLFW_PRESS: {
                    MouseButtonPressedEvent event(data.WindowPtr, button);
                    data.EventCallback(event); // calling the callback function 
                    break;
                }
                case GLFW_RELEASE: {
                    MouseButtonReleasedEvent event(data.WindowPtr, button);
                    data.EventCallback(event); // calling the callback function 
                    break;
                }
            }
        });
        glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset) {
            WindowData& data = *reinterpret_cast<WindowData*>(glfwGetWindowUserPointer(window));

            MouseScrolledEvent event(data.WindowPtr, (float)xOffset, (float)yOffset);
            data.EventCallback(event); // calling the callback function 
        });
        glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos) {
            WindowData& data = *reinterpret_cast<WindowData*>(glfwGetWindowUserPointer(window));

            MouseMovedEvent event(data.WindowPtr, (float)xPos, (float)yPos);
            data.EventCallback(event); // calling the callback function 
        });

        glfwMakeContextCurrent(nullptr); // unbind for memory issues
        return true;
    }
    void OpenGLWindow::SetTitle(const std::string& title) {
        m_Data.Title = title;
        glfwSetWindowTitle(m_Window, title.c_str()); // set window title
    }
    void OpenGLWindow::SetSize(int width, int height) {
        m_Data.Width = width;
        m_Data.Height = height; // modifies all instances of m_Data
        glfwSetWindowSize(m_Window, width, height); // set window size
    }

    void OpenGLWindow::PollWindowEvents() {
        glfwPollEvents(); // poll events for all windows
    }

    void OpenGLWindow::BeforeLoop() {
        glfwMakeContextCurrent(m_Window);
    }
    void OpenGLWindow::AfterLoop() {
        VG_CORE_INFO("Ending window loop: {0}", m_Data.Title);
        glfwMakeContextCurrent(nullptr); // release ptr
    }
    void OpenGLWindow::BeginFrame() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
    /* Context reliant */
    void OpenGLWindow::EndFrame() {
        glfwSwapBuffers(m_Window);
    }


    
}