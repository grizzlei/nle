#ifndef NLE_SIGNAL_HPP
#define NLE_SIGNAL_HPP

#include <thread>
#include <vector>
#include <functional>

#include "Utils.h"

namespace nle
{
    template <typename T>
    class Signal
    {
    public:
        typedef std::function<void(const T &)> callback_t;

        Signal()
        {
        }

        void emit(const T &message)
        {
            for (const auto &it : m_callbacks)
            {
                try
                {
                    std::thread(it, message).detach();
                }
                catch (const std::exception &e)
                {
                    prerr("%s", e.what());
                }
            }
        }

        void bindCallback(callback_t callback)
        {
            m_callbacks.push_back(callback);
        }

    private:
        std::vector<callback_t> m_callbacks;
    };
} // namespace nle

#endif