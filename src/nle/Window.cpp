#include "Window.h"

namespace nle
{

    Window::Window(GLuint w, GLuint h, const std::string &title)
    {
        m_input_handler = new InputHandler();

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
        glfwSetWindowShouldClose(m_handle, GLFW_TRUE);
    }

    InputHandler *Window::input_handler()
    {
        return m_input_handler;
    }

    void Window::set_draw_callback(std::function<void()> dcb)
    {
        m_draw_callback = dcb;
    }

    void Window::set_cursor_visibility(bool visible)
    {
        glfwSetInputMode(m_handle, GLFW_CURSOR, (m_show_cursor = visible) ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
    }

    bool Window::cursor_visibility()
    {
        return m_show_cursor;
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

    bool Window::fullscreen()
    {
        return m_fullscreen;
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

        if (key >= 0 && key < w->m_input_handler->keys().size())
        {
            if (action == GLFW_PRESS)
            {
                w->m_input_handler->set_key_state(key, true);
            }
            else if (action == GLFW_RELEASE)
            {
                w->m_input_handler->set_key_state(key, false);
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
        w->m_input_handler->set_mouse_state(mouse_x, mouse_y);
    }
} // namespace nle
