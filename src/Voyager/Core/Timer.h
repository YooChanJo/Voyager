#pragma once
#include "pch.h"

namespace Voyager {
    class Timer {
    private:
        std::chrono::steady_clock::time_point m_Start;
    public:
        Timer();

        void Reset();
        double Elapsed(); // seconds
        double ElapsedMillis(); // millies
    };
}
