#include "InputHandler.h"

namespace nle
{

void InputHandler::set_key_state(int key, bool state)
{
    m_keys[key] = state;
}

const std::array<bool, 1024> &InputHandler::keys()
{
    m_keys;
}

bool InputHandler::key_state(int key)
{
    return m_keys[key];
}

Signal<int> &InputHandler::key_pressed()
{
    return sig_key_pressed;
}

Signal<int> &InputHandler::key_released()
{
    return sig_key_released;
}

} // namespace nle
