#ifndef WINDOW_H
#define WINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <any>
#include <string>
#include <atomic>
#include <stdexcept>
#include <functional>

#include "Utils.h"

#define NLE_WINDOW_DEFAULT_WIDTH    1280
#define NLE_WINDOW_DEFAULT_HEIGHT   720

namespace nle
{
    class Window
    {
    private:
        GLFWwindow *m_handle;
        std::atomic_bool m_closed;
        std::function<void()> m_draw_callback;
        int m_width;
        int m_height;
        std::array<bool, 1024> m_keys;

        glm::vec2 m_mouse_last;
        glm::vec2 m_mouse_delta;
        bool m_mouse_moved_once;
        bool m_fullscreen;

        static void key_handler(GLFWwindow *window, int key, int code, int action, int mode);
        static void mouse_handler(GLFWwindow *window, double mouse_x, double mouse_y);

    public:
        Window(GLuint w, GLuint h, const std::string &title);
        ~Window();
        void set_draw_callback(std::function<void()> dcb);
        void set_cursor_visibility(bool visible);
        void set_fullscreen(bool fullscreen);
        bool closed();
        void display();
        void close();

        friend class Renderer3D;
    };
} // namespace nle

#endif