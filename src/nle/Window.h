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
        std::function<void()> m_drawCallback;
        int m_width;
        int m_height;
        std::array<bool, 1024> m_keys;

        glm::vec2 m_mouseLast;
        glm::vec2 m_mouseDelta;
        bool m_mouseMovedOnce;
        bool m_fullScreen;

        static void keyHandler(GLFWwindow *window, int key, int code, int action, int mode);
        static void mouseHandler(GLFWwindow *window, double posX, double posY);

    public:
        Window(GLuint w, GLuint h, const std::string &title);
        ~Window();
        void setDrawCallback(std::function<void()> dcb);
        void setCursorVisibility(bool visible);
        void setFullScreen(bool fullscreen);
        bool closed();
        void display();
        void close();

        friend class Renderer3D;
    };
} // namespace nle

#endif