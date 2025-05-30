#define USE_ENTRY_POINT 1
#if USE_ENTRY_POINT
#include "Voyager/Core/EntryPoint.h"

using namespace Voyager;

// #include "Voyager/API/OpenGL/Renderers/BatchRenderer2D.h"
// #include "Voyager/Graphics/Sprite.h"
// #include "Voyager/Graphics/Group.h"

// #include "Voyager/Core/Input.h"
// #include <imgui.h>

// class TestLayer : public Layer {
// private:
//     Scope<BatchRenderer2D> batchRenderer;
//     std::vector<Sprite*> sprites;
//     Scope<Group> shiftGroup;
// public:
//     TestLayer() : Layer("Test Layer") {
//         VG_CORE_INFO("TestLayer created!");
//     }
//     ~TestLayer() {
//         VG_CORE_INFO("TestLayer destroyed!");
//         for(auto sprite : sprites) {
//             delete sprite;
//         }
//     }

//     void OnAttach() override {
//         glfwMakeContextCurrent((GLFWwindow*)(Application::Get().GetWindow()->GetNativeWindow())); // main thread --> impossible
//         batchRenderer = CreateScope<BatchRenderer2D>();
//         batchRenderer->ProvideShader("C:/Users/Owner/Desktop/project/Voyager/shaders/batch.shader");
//         batchRenderer->GetShader().Bind();
//         batchRenderer->GetShader().SetUniform1f("u_WindowHeight", (float)Application::Get().GetWindow()->GetHeight());
//         srand(time(NULL));
//         shiftGroup = CreateScope<Group>(glm::translate(glm::mat4(1.0f), glm::vec3(0, 2.5, 0)));

// #define TEST_50K_SPRITES 0
// #if TEST_50K_SPRITES
//         for(float y = 0; y < 9.0f; y += 0.05f) {
//             for(float x = 0; x < 16.0f; x += 0.05f) {
//                 // sprites.push_back(new Sprite(x, y, 0.04f, 0.04f, glm::vec4(rand() % 1000 / 1000.0f, 0, 1, 1)));
//                 shiftGroup->Add(new Sprite(x, y, 0.04f, 0.04f, glm::vec4(rand() % 1000 / 1000.0f, 0, 1, 1)));
//             }
//         }
// #else
//         for(float y = 0; y < 9.0f; y += 1.0f) {
//             for(float x = 0; x < 16.0f; x += 1.0f) {
//                 // sprites.push_back(new Sprite(x, y, 0.9f, 0.9f, glm::vec4(rand() % 1000 / 1000.0f, 0, 1, 0.5)));
//                 shiftGroup->Add(new Sprite(x, y, 0.9f, 0.9f, glm::vec4(rand() % 1000 / 1000.0f, 0, 1, 0.5)));
//             }
//         }
// #endif
//         glm::mat4 mvp = glm::ortho(0.0f, 16.0f, 0.0f, 9.0f);

//         batchRenderer->GetShader().SetUniformMat4f("u_MVP", mvp);
//         glfwMakeContextCurrent(nullptr);
//     }

//     void OnImGuiRender() override {
//         {
//             static bool show = true;
//             // ImGui::Begin("MainDockSpace", nullptr, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking);

//             // ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
//             // ImGui::DockSpace(dockspace_id);

//             if(show) ImGui::ShowDemoWindow(&show);

//             // ImGui::End();
//         }
//     }

//     void OnUpdate() override {
//         batchRenderer->Begin();
//         shiftGroup->Submit(batchRenderer.get());
//         // int i = 0;
//         // for(auto sprite : sprites) {
//         //     if(i++ % 2 == 0) batchRenderer->Push(glm::translate(glm::mat4(1.0f), glm::vec3(2.5, 0, 0)));
//         //     else batchRenderer->Push(glm::translate(glm::mat4(1.0f), glm::vec3(0, 2.5, 0)));
//         //     batchRenderer->Submit(sprite);
//         //     batchRenderer->Pop();
//         // }
//         batchRenderer->End();
//         batchRenderer->Flush();
//     }

//     Scope<BatchRenderer2D>& GetBatchRenderer() {
//         return batchRenderer;
//     }


//     void OnEvent(const EventPtr& e) override {
//         EventDispatcher dispatcher(e);
//         OpenGLShader& shader = batchRenderer->GetShader();
//         dispatcher.Dispatch<MouseMovedEvent>([&shader](const MouseMovedEventPtr& event) {
//             // VG_CORE_INFO("Mouse moved to: {0}, {1}", event->GetX(), event->GetY());
//             glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
//             shader.Bind();
//             shader.SetUniform2f("u_MousePos", event->GetX(), event->GetY());
//             return true;
//         });
//         dispatcher.Dispatch<WindowResizeEvent>([&shader](const WindowResizeEventPtr& event) {
//             shader.Bind();
//             shader.SetUniform1f("u_WindowHeight", (float)event->GetHeight());
//             return true;
//         });
//         dispatcher.Dispatch<KeyPressedEvent>([](const KeyPressedEventPtr& event) {
//             Application::Get().GetWindow()->SetTitle("pressed");
//             return true;
//         });
//         dispatcher.Dispatch<KeyReleasedEvent>([](const KeyReleasedEventPtr& event) {
//             Application::Get().GetWindow()->SetTitle("Released");
//             return true;
//         });
//     }
// };

#include "Renderer/Renderer.h"
#include <imgui.h>

#define APPLICATION_WINDOW (Application::Get().GetWindow())

class BasicRenderLayer: public Layer {
private:
    Ref<VertexArray> m_VAO;
    Ref<Shader> m_Shader;
    glm::mat4 m_Transform;
    Scope<Renderer> m_Renderer;

public:
    BasicRenderLayer(): Layer("Basic Render Layer") {
        VG_CORE_WARN("Basic Render Layer created");
    }
    ~BasicRenderLayer() {}
    
    void OnAttach() override {
        RenderCommand::SetViewport(0, 0, APPLICATION_WINDOW->GetWidth(), APPLICATION_WINDOW->GetHeight());
        m_VAO = VertexArray::Create();
        m_VAO->Bind();

        float vertices[] = {
            -0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 1.0f,
             0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f,
             0.5f,  0.5f, 1.0f, 0.0f, 1.0f, 1.0f,
            -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f,
        };
        Ref<VertexBuffer> vertex_buffer = VertexBuffer::Create(vertices, sizeof(vertices));
        BufferLayout layout = {
            { ShaderDataType::Float2, "a_Position" },
            { ShaderDataType::Float4, "a_Color" }
        };
        vertex_buffer->SetLayout(layout);
        m_VAO->AddVertexBuffer(vertex_buffer);

        uint32_t indices[] = { 0, 1, 2, 2, 3, 0 };
        m_VAO->SetIndexBuffer(IndexBuffer::Create(indices, 6));

        m_VAO->Unbind();

        m_Transform = glm::mat4(1.0f); // the identity matrix
        m_Shader = Shader::Create("shaders/square.shader");

        m_Renderer = CreateScope<Renderer>(); 
    }
private:
    bool m_ImGuiWindowOpen = true;
public:
    void OnDetach() override {
        VG_CORE_WARN("Destroyed Basic Render Layer");
    }
    void OnImGuiRender() override {
        if(m_ImGuiWindowOpen) {
            ImGui::ShowDemoWindow(&m_ImGuiWindowOpen);
        }
    }
    void OnUpdate() override {
        m_Renderer->BeginScene();
        m_Renderer->Submit(m_Shader, m_VAO, m_Transform);
        m_Renderer->EndScene();
    }
    void OnEvent(const EventPtr& event) override {

    }
};


class TestApplication : public Application {
public:
    TestApplication()
        : Application(GraphicsAPI::OpenGL)
    {
        // GetWindow()->PushLayer(CreateScope<TestLayer>());
        GetWindow()->PushLayer(CreateScope<BasicRenderLayer>());
    }
    virtual ~TestApplication() {

    }
};

namespace Voyager {
    Application* CreateApplication(ApplicationCommandLineArgs args) {
        TestApplication* app = new TestApplication();

        return app;
    }
}


#else
#include "pch.h"
#include "Events/Event.h"
#include "Events/MouseEvent.h"
#include "Events/ApplicationEvent.h"

#include "API/OpenGL/OpenGLWindow.h"
#include "API/OpenGL/OpenGLVertexArray.h"
#include "API/OpenGL/OpenGLVertexBuffer.h"
#include "API/OpenGL/OpenGLVertexBufferLayout.h"
#include "API/OpenGL/OpenGLIndexBuffer.h"
#include "API/OpenGL/OpenGLShader.h"
#include "API/OpenGL/OpenGLTexture.h"

#include "API/OpenGL/Renderers/BasicTextureRenderer.h"
#include "API/OpenGL/Renderers/Simple2DRenderer.h"
#include "API/OpenGL/Renderers/BatchRenderer2D.h"

#include "Graphics/Sprite.h"

#include "Utils/Timer.h"


using namespace Voyager;


#define USE_BASIC_TEXTURE_RENDERER 0
#define USE_SIMPLE_2D_RENDERER 0
#define USE_BATCH_RENDERER 1
#define TEST_50K_SPRITES 0
int main() {
    /* 
        Need to make renderer stop when window closes --> handled
        Need to speed up the entire process of handling events --> async await
        Multiple window support is very weak and slow --> Use multithreading
    */

#if USE_BASIC_TEXTURE_RENDERER
    // basic renderer
    OpenGLWindow windowBasic("Basic Renderer Test Window");
    const GLubyte* version = glGetString(GL_VERSION);
    VG_CORE_INFO("OpenGL version: {0}", reinterpret_cast<const char*>(version));
    
    BasicTextureRenderer renderer_basic(windowBasic);

    float positions[] = {
        -0.5f, -0.5f, 0.0f, /* 1.0f, 0.0f, 0.0f, 1.0f, */  0.0f, 0.0f, // 0
         0.5f, -0.5f, 0.0f, /* 1.0f, 0.0f, 0.0f, 1.0f, */  1.0f, 0.0f, // 1
         0.5f,  0.5f, 0.0f, /* 1.0f, 0.0f, 0.0f, 1.0f, */  1.0f, 1.0f, // 2
        -0.5f,  0.5f, 0.0f, /* 1.0f, 0.0f, 0.0f, 1.0f, */  0.0f, 1.0f, // 3
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0,
    };

    VertexArray va;

    VertexBuffer vb(positions, (3 + 4) * 4 * sizeof(float));
    VertexBufferLayout layout;
    layout.Push<float>(3); // position
    // layout.Push<float>(4); // color
    layout.Push<float>(2); // texture coord

    IndexBuffer ib(indices, 6);
    Shader shader("C:/Users/Owner/Desktop/project/Voyager/shaders/texture.shader");
    Texture texture("C:/Users/Owner/Desktop/project/Voyager/textures/beautiful_sunset.jpg");

    renderer_basic.AddVertexArray(va);
    renderer_basic.AddVertexBufferAndLayout(vb, layout);
    renderer_basic.AddIndexBuffer(ib);
    renderer_basic.AddShader(shader); // shader generated

    renderer_basic.AddTexture(texture, "BeautifulSunset", 0); // texture generated
    windowBasic.EnableBlending();

    // shader.Bind();
    // shader.SetUniform1f("u_WindowHeight", (float)windowBasic.GetHeight());
        
    // windowBasic.SetEventCallback([&shader, &windowBasic](Event& e){
    //     EventDispatcher dispatcher(e);
    //     windowBasic.MakeWindowContextCurrent();
    //     dispatcher.Dispatch<MouseMovedEvent>([&shader](MouseMovedEvent& event) {
    //         shader.Bind();
    //         shader.SetUniform2f("u_MousePos", event.GetX(), event.GetY());
    //         return true;
    //     });
    //     dispatcher.Dispatch<WindowResizeEvent>([&shader](WindowResizeEvent& event) {
    //         shader.Bind();
    //         shader.SetUniform1f("u_WindowHeight", (float)event.GetHeight());
    //         return true;
    //     });
    // });
#endif

#if USE_SIMPLE_2D_RENDERER
    // simple 2d renderer
    OpenGLWindow windowSimple2D("Simple 2D Renderer Test Window");
    Simple2DRenderer renderer_simple_2D(windowSimple2D);

    Renderable2D sprite(glm::vec3(5.0f, 5.0f, 0.0f), glm::vec2(4.0f, 4.0f), glm::vec4(1.0f, 0.0f, 1.0f, 1.0f));
    Renderable2D another_sprite(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(4.0f, 8.0f), glm::vec4(0.0f, 0.5f, 1.0f, 1.0f));

    renderer_simple_2D.ProvideShader("C:/Users/Owner/Desktop/project/Voyager/shaders/simple_2d.shader");

    renderer_simple_2D.GetShader().Bind();
    renderer_simple_2D.GetShader().SetUniform1f("u_WindowHeight", (float)windowSimple2D.GetHeight());

    glm::mat4 perspectiveMatrix = glm::ortho(0.0f, 15.0f, 0.0f, 15.0f);

    renderer_simple_2D.GetShader().SetUniformMat4f("u_MVP", perspectiveMatrix);

    windowSimple2D.SetEventCallback([&renderer_simple_2D, &windowSimple2D](Event& e){
        EventDispatcher dispatcher(e);
        windowSimple2D.MakeWindowContextCurrent();
        dispatcher.Dispatch<MouseMovedEvent>([&renderer_simple_2D](MouseMovedEvent& event) {
            renderer_simple_2D.GetShader().Bind();
            renderer_simple_2D.GetShader().SetUniform2f("u_MousePos", event.GetX(), event.GetY());
            return true;
        });
        dispatcher.Dispatch<WindowResizeEvent>([&renderer_simple_2D](WindowResizeEvent& event) {
            renderer_simple_2D.GetShader().Bind();
            renderer_simple_2D.GetShader().SetUniform1f("u_WindowHeight", (float)event.GetHeight());
            return true;
        });
    });
#endif

#if USE_BATCH_RENDERER
    OpenGLWindow windowBatch("Batch Renderer Test Window");
    BatchRenderer2D renderer_batch(windowBatch);

    renderer_batch.ProvideShader("C:/Users/Owner/Desktop/project/Voyager/shaders/batch.shader");
    renderer_batch.GetShader().Bind();
    renderer_batch.GetShader().SetUniform1f("u_WindowHeight", (float)windowBatch.GetHeight());
    
    srand(time(NULL));

    std::vector<Sprite*> sprites;
#if TEST_50K_SPRITES
    for(float y = 0; y < 9.0f; y += 0.05f) {
        for(float x = 0; x < 16.0f; x += 0.05f) {
            sprites.push_back(new Sprite(x, y, 0.04f, 0.04f, glm::vec4(rand() % 1000 / 1000.0f, 0, 1, 1)));
        }
    }
#else    
    for(float y = 0; y < 9.0f; y += 1.0f) {
        for(float x = 0; x < 16.0f; x += 1.0f) {
            sprites.push_back(new Sprite(x, y, 0.9f, 0.9f, glm::vec4(rand() % 1000 / 1000.0f, 0, 1, 0.5)));
        }
    }
    windowBatch.EnableBlending();
#endif
    glm::mat4 mvp = glm::ortho(0.0f, 16.0f, 0.0f, 9.0f);

    renderer_batch.GetShader().SetUniformMat4f("u_MVP", mvp);

    windowBatch.SetEventCallback([&renderer_batch, &windowBatch](Event& e){
        EventDispatcher dispatcher(e);
        windowBatch.MakeWindowContextCurrent();
        dispatcher.Dispatch<MouseMovedEvent>([&renderer_batch](MouseMovedEvent& event) {
            renderer_batch.GetShader().Bind();
            renderer_batch.GetShader().SetUniform2f("u_MousePos", event.GetX(), event.GetY());
            return true;
        });
        dispatcher.Dispatch<WindowResizeEvent>([&renderer_batch](WindowResizeEvent& event) {
            renderer_batch.GetShader().Bind();
            renderer_batch.GetShader().SetUniform1f("u_WindowHeight", (float)event.GetHeight());
            return true;
        });
    });
#endif
    
    Timer timer;
    unsigned int counter = 0u;
    unsigned int frames = 0;
    while(!(/* windowBasic.IsClosed() && windowSimple2D.IsClosed() &&  */windowBatch.IsClosed())) {
        
#if USE_BASIC_TEXTURE_RENDERER
        windowBasic.MakeWindowContextCurrent();
        windowBasic.Clear();
        renderer_basic.Draw();
        windowBasic.EndFrame();
#endif
#if USE_SIMPLE_2D_RENDERER
        windowSimple2D.MakeWindowContextCurrent();
        windowSimple2D.Clear();
        renderer_simple_2D.Submit(&sprite);
        renderer_simple_2D.Submit(&another_sprite);
        renderer_simple_2D.Flush();
        windowSimple2D.EndFrame();
#endif

#if USE_BATCH_RENDERER
        windowBatch.MakeWindowContextCurrent();
        windowBatch.Clear();
        renderer_batch.Begin();
        int i = 0;
        for(auto sprite : sprites) {
            if(i++ % 2 == 0) renderer_batch.Push(glm::translate(glm::mat4(1.0f), glm::vec3(2.5, 0, 0)));
            else renderer_batch.Push(glm::translate(glm::mat4(1.0f), glm::vec3(0, 2.5, 0)));
            renderer_batch.Submit(sprite);
            renderer_batch.Pop();
        }
        renderer_batch.End();
        renderer_batch.Flush();
        windowBatch.EndFrame();
#endif
        if(timer.Elapsed() - counter > 1.0) {
            printf("FPS: %d\n", frames);
            counter++;
            frames = 0;
        }
        frames++;
    }
#if USE_BATCH_RENDERER
    for(auto sprite : sprites) {
        delete sprite;
    }
#endif
    return 0;
}
#endif