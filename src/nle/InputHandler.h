#pragma once

#include "Signal.hpp"

#include <array>

namespace nle
{

class InputHandler
{
private:
    std::array<bool, 1024> m_keys;
    void set_key_state(int key, bool state);
    Signal<int> sig_key_pressed;
    Signal<int> sig_key_released;

public:
    InputHandler() = default;

    const std::array<bool, 1024>& keys();
    bool key_state(int key);
    Signal<int>& key_pressed();
    Signal<int>& key_released();

    friend class Window;
};

} // namespace nle
