#include "Timer.h"

namespace Voyager {
    Timer::Timer() {
        Reset();
    }

    void Timer::Reset() {
        m_Start = std::chrono::steady_clock::now();
    }

    double Timer::Elapsed() {
        auto current = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed = current - m_Start;
        return elapsed.count(); // returns seconds as double
    }

    double Timer::ElapsedMillis() {
        return Elapsed() * 1000.0;
    }
}
