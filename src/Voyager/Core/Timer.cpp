#include "Timer.h"

namespace Voyager {
    Timer::Timer() {
        Reset();
    }

    void Timer::Reset() {
        m_Start = std::chrono::steady_clock::now();
    }

    float Timer::Elapsed() {
        auto current = std::chrono::steady_clock::now();
        std::chrono::duration<float> elapsed = current - m_Start;
        return elapsed.count(); // returns seconds as double
    }

    float Timer::ElapsedMillis() {
        return Elapsed() * 1000.0f;
    }
}
