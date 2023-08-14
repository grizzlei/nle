#pragma once

#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>

#include <GLFW/glfw3.h>

namespace nle
{
    namespace imgui
    {
        
    }

class ImGUI_GLFW
{
private:
    GLFWwindow *m_handle;
    bool m_visible = true;
public:
    ImGUI_GLFW(GLFWwindow *handle, unsigned int glsl_version = 330);
    ~ImGUI_GLFW();
    void render();

    bool visible() const;
    void set_visible(bool visible);
};

} // namespace nle
