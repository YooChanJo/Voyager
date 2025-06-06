#pragma once
#include "pch.h"

namespace Voyager {
    class Timer {
    private:
        std::chrono::steady_clock::time_point m_Start;
    public:
        Timer();

        void Reset();
        float Elapsed(); // seconds
        float ElapsedMillis(); // millies
    };
}
