#pragma once

#define MILLISECONDS 1000.0
#define MICROSECONDS 1000000.0
#define NANOSECONDS 1000000000.0


#include <windows.h>
#include <iostream>

//Class for getting accurate time diffs with QueryPerformanceCounter
class TimeMeasurement {
    double PCFreq = 0.0;
    __int64 CounterStart = 0;
    LARGE_INTEGER li{};

    void reset() {
        PCFreq = 0.0;
        CounterStart = 0;
    }

public:
    //Function that starts measuring time after restarting the clock
    void startCounting()
    {
        reset();
        if (!QueryPerformanceFrequency(&li)) {
            std::cout << "QueryPerformanceFrequency failed!\n";
        }

        PCFreq = double(li.QuadPart) / MILLISECONDS;

        QueryPerformanceCounter(&li);
        CounterStart = li.QuadPart;
    }

    //Function for getting elapsed time diff
    double getTime()
    {
        QueryPerformanceCounter(&li);
        return double(li.QuadPart - CounterStart) / PCFreq;
    }

};