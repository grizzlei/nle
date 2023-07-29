#ifndef NLE_SIGNAL_HPP
#define NLE_SIGNAL_HPP

#include <thread>
#include <vector>
#include <functional>

#include "Utils.h"

namespace nle
{
    template <typename T, typename ...ExtraArgs>
    class Signal
    {
    public:
        typedef std::function<void(const T & message, ExtraArgs... args)> callback_t;

        Signal()
        {
        }

        void emit(const T &message, ExtraArgs... args)
        {
            for (const auto &it : m_callbacks)
            {
                try
                {
                    std::thread(it, message, args...).detach();
                }
                catch (const std::exception &e)
                {
                    prerr("%s", e.what());
                }
            }
        }

        void bind_callback(callback_t callback)
        {
            m_callbacks.push_back(callback);
        }

    private:
        std::vector<callback_t> m_callbacks;
    };
} // namespace nle

#endif