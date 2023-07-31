#include "Window.h"

namespace nle
{

    Window::Window(GLuint w, GLuint h, const std::string &title)
    {
        GLenum err = glfwInit();
        if (err != GLFW_TRUE)
        {
            throw std::runtime_error("fatal_error: could not initialize glfw. error code: " + std::to_string(err));
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

        m_handle = glfwCreateWindow(w, h, title.c_str(), nullptr, nullptr);
        glfwMakeContextCurrent(m_handle);

        err = glewInit();
        if (err != GLEW_OK)
        {
            throw std::runtime_error("fatal_error: could not initialize glew. error code: " + std::to_string(err));
        }

        const GLubyte* vendor = glGetString(GL_VENDOR);
        const GLubyte* renderer = glGetString(GL_RENDERER);
        prinf("%s", (char*)vendor);
        prinf("%s", (char*)renderer);

        glfwSetWindowUserPointer(m_handle, this);
        glfwSetKeyCallback(m_handle, Window::key_handler);
        glfwSetCursorPosCallback(m_handle, Window::mouse_handler);
    }

    Window::~Window()
    {
        glfwDestroyWindow(m_handle);
        glfwTerminate();
    }

    void Window::display()
    {
        while (!glfwWindowShouldClose(m_handle))
        {
            glfwGetWindowSize(m_handle, &m_width, &m_height);

            if (m_draw_callback)
            {
                m_draw_callback();
            }
            
            glfwSwapBuffers(m_handle);
            glfwPollEvents();
        }
        m_closed = true;
    }

    void Window::close()
    {
        // glfwDestroyWindow(m_handle);
    }

    void Window::set_draw_callback(std::function<void()> dcb)
    {
        m_draw_callback = dcb;
    }

    void Window::set_cursor_visibility(bool visible)
    {
        glfwSetInputMode(m_handle, GLFW_CURSOR, visible ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
    }

    void Window::set_fullscreen(bool fullscreen)
    {
        if((m_fullscreen = fullscreen))
        {
            const GLFWvidmode * vm = glfwGetVideoMode(glfwGetPrimaryMonitor());
            glfwSetWindowMonitor(m_handle, glfwGetPrimaryMonitor(), 0, 0, vm->width, vm->height, vm->refreshRate);
        }
        else
        {
            glfwSetWindowMonitor(m_handle, nullptr, 0, 0, NLE_WINDOW_DEFAULT_WIDTH, NLE_WINDOW_DEFAULT_HEIGHT, 0);
        }
    }

    bool Window::closed()
    {
        return m_closed;
    }

    void Window::key_handler(GLFWwindow *window, int key, int code, int action, int mode)
    {
        Window *w = static_cast<Window *>(glfwGetWindowUserPointer(window));
        if (!w)
        {
            return;
        }

        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(w->m_handle, GL_TRUE);
        }

        if(key == GLFW_KEY_F && action == GLFW_PRESS)
        {
            w->set_fullscreen(!w->m_fullscreen);
        }

        if(key == GLFW_KEY_LEFT_CONTROL && action == GLFW_PRESS)
        {
            bool visible = glfwGetInputMode(w->m_handle, GLFW_CURSOR) == GLFW_CURSOR_NORMAL;
            w->set_cursor_visibility(!visible);
        }

        if (key >= 0 && key < w->m_keys.size())
        {
            if (action == GLFW_PRESS)
            {
                w->m_keys[key] = true;
            }
            else if (action == GLFW_RELEASE)
            {
                w->m_keys[key] = false;
            }
        }
    }

    void Window::mouse_handler(GLFWwindow *window, double mouse_x, double mouse_y)
    {
        Window *w = static_cast<Window *>(glfwGetWindowUserPointer(window));
        if (!w)
        {
            return;
        }

        if (!w->m_mouse_moved_once)
        {
            w->m_mouse_last = {mouse_x, mouse_y};
            w->m_mouse_moved_once = true;
            return;
        }

        glm::vec2 now = glm::vec2(mouse_x, mouse_y);

        w->m_mouse_delta.x = now.x - w->m_mouse_last.x;
        // because y increases going downwards on the screen.
        w->m_mouse_delta.y = w->m_mouse_last.y - now.y;

        w->m_mouse_last = now;
        // prdbg("mouse dx: %.6f dy: %.6f", w->m_mouse_delta.x, w->m_mouse_delta.y);
    }
} // namespace nle
