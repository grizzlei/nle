#include "InputHandler.h"

#define NLE_INPUT_PROCESS_SLEEP_TIME_MS     16666

namespace nle
{

InputHandler::InputHandler(GLFWwindow *handle)
    : m_handle(handle)
{
    m_thr_input = std::thread([this](){
        while (!glfwWindowShouldClose(m_handle))
        {
            for(int i = 0; i < m_keys.size(); i++)
            {
                if(m_keys[i])
                {
                    sig_key_pressed.emit(i, false);
                }
            }

            std::this_thread::sleep_for(std::chrono::microseconds(NLE_INPUT_PROCESS_SLEEP_TIME_MS));
        }
    });
}

InputHandler::~InputHandler()
{
}

void InputHandler::set_key_state(int key, bool state)
{
    m_keys[key] = state;
}

void InputHandler::set_mouse_position(int x, int y)
{
    if(!m_mouse_moved_once)
    {
        m_mouse_last_x = x;
        m_mouse_last_y = y;
        m_mouse_moved_once = true;
        return;
    }

    m_mouse_delta_x = x - m_mouse_last_x;
    m_mouse_delta_y = m_mouse_last_y - y;

    m_mouse_last_x = x;
    m_mouse_last_y = y;

    sig_mouse_moved.emit(m_mouse_delta_x, m_mouse_delta_y, false);
}

void InputHandler::set_mouse_button_state(int button, bool state)
{
    m_mouse_buttons[button] = state;
    sig_mouse_state_changed.emit(button, state, m_mouse_last_x, m_mouse_last_y, false);
}

const std::array<bool, 1024> &InputHandler::keys()
{
    return m_keys;
}

bool InputHandler::key_state(int key)
{
    return m_keys[key];
}

Signal<int> &InputHandler::key_pressed()
{
    return sig_key_pressed;
}

Signal<int> &InputHandler::key_just_pressed()
{
    return sig_key_just_pressed;
}

Signal<int> &InputHandler::key_released()
{
    return sig_key_released;
}

Signal<int, int> &InputHandler::mouse_moved()
{
    return sig_mouse_moved;
}

Signal<int, bool, int, int> &InputHandler::mouse_button_state_changed()
{
    return sig_mouse_state_changed;
}

int InputHandler::mouse_x()
{
    return m_mouse_last_x;
}

int InputHandler::mouse_y()
{
    return m_mouse_last_y;
}

int InputHandler::mouse_dx()
{
    return m_mouse_delta_x;
}

int InputHandler::mouse_dy()
{
    return m_mouse_delta_y;
}

} // namespace nle
