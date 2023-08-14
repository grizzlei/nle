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

        void emit(const T &message, ExtraArgs... args, bool async = true)
        {
            for (const auto &it : m_callbacks)
            {
                if(async)
                {
                    std::thread(it, message, args...).detach();
                }
                else
                {
                    it(message, args...);
                }
            }
        }

        void bind_callback(callback_t callback)
        {
            m_callbacks.push_back(callback);
        }

        void unbind_all()
        {
            m_callbacks.clear();
        }

    private:
        std::vector<callback_t> m_callbacks;
    };
} // namespace nle

#endif