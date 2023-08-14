#include "ImGUI_GLFW.h"
#include "Utils.h"

#include <string>

namespace nle
{

    ImGUI_GLFW::ImGUI_GLFW(GLFWwindow *handle, unsigned int glsl_version)
        : m_handle(handle)
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; 
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        ImGui_ImplGlfw_InitForOpenGL(m_handle, true);

        std::string version = "#version " + std::to_string(glsl_version);

        ImGui_ImplOpenGL3_Init(version.c_str());
        ImGui::StyleColorsDark();
    }

    ImGUI_GLFW::~ImGUI_GLFW()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void ImGUI_GLFW::render()
    {
        // ImGui::Begin("nice little engine", nullptr);
        // create frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        if(ImGui::BeginMainMenuBar())
        {
            if(ImGui::BeginMenu("File"))
            {
                if(ImGui::MenuItem("Load Model"))
                {
                    prdbg("Load Model");
                }
                
                if(ImGui::MenuItem("Quit"))
                {
                    prdbg("Quit");
                }
                
                ImGui::EndMenu();
            }

            ImGui::EndMainMenuBar();
        }

        if(ImGui::Begin("nice little engine", nullptr, ImGuiWindowFlags_MenuBar))
        {
            ImGui::TextWrapped("https://github.com/grizzlei/nle");
            ImGui::TextWrapped("hasan karaman - 2023");
            ImGui::TextWrapped("experimental opengl renderer and physics engine.");
            ImGui::Separator();
            ImGui::TextWrapped("controls:");
            ImGui::TextWrapped("[ctrl] - enable/disable free roam");
            ImGui::TextWrapped("[f] - enable/disable fullscreen");

            
            ImGui::End();
        }


        // static bool show_demo_window = true;
        // ImGui::ShowDemoWindow(&show_demo_window);

        // render
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    bool ImGUI_GLFW::visible() const
    {
        return m_visible;
    }

    void ImGUI_GLFW::set_visible(bool visible)
    {
        m_visible = visible;
    }

} // namespace nle
