#ifndef UTILS_H
#define UTILS_H

#include <random>
#include <string>
#include <array>
#include <cstring>
#include <functional>
#include <algorithm>

// #define DEBUG   1

#if defined(DEBUG)
#define prdbg(x, ...) (printf("\x1b[33mnle::dbg: " x "\x1b[0m\n", ##__VA_ARGS__))
#else
#define prdbg(x, ...) ()
#endif

#define prerr(x, ...) (printf("\x1b[31mnle::err: " x "\x1b[0m\n", ##__VA_ARGS__))
#define prwar(x, ...) (printf("\x1b[36mnle::wrn: " x "\x1b[0m\n", ##__VA_ARGS__))
#define prinf(x, ...) (printf("\x1b[32mnle::inf: " x "\x1b[0m\n", ##__VA_ARGS__))

#define PI 3.14159265
#define rad2deg(x) (x * 180.f / PI)
#define deg2rad(x) (x * PI / 180.f)

namespace nle
{
    const constexpr unsigned int UID_LEN = 16;

    template <typename T = std::mt19937>
    inline auto random_generator() -> T
    {
        auto constexpr seed_bytes = sizeof(typename T::result_type) * T::state_size;
        auto constexpr seed_len = seed_bytes / sizeof(std::seed_seq::result_type);
        auto seed = std::array<std::seed_seq::result_type, seed_len>();
        auto dev = std::random_device();
        std::generate_n(begin(seed), seed_len, std::ref(dev));
        auto seed_seq = std::seed_seq(begin(seed), end(seed));
        return T{seed_seq};
    }

    inline std::string generate_random_alphanumeric_string(std::size_t len = UID_LEN)
    {
        static constexpr auto chars =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";
        thread_local auto rng = random_generator<>();
        auto dist = std::uniform_int_distribution{{}, std::strlen(chars) - 1};
        auto result = std::string(len, '\0');
        std::generate_n(begin(result), len, [&]()
                        { return chars[dist(rng)]; });
        return result;
    }

    inline double get_time_sec()
    {
        struct timespec now = {0, 0};
        clock_gettime(CLOCK_MONOTONIC, &now);
        return (double)now.tv_sec + 1e-9 * now.tv_nsec;
    }
} // namespace nle

#endif