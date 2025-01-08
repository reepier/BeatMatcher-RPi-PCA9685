#pragma once
#include <stdlib.h>
#include <cmath>

#include "wiringPi.h"
#include "config.h"

// linearly interpolates (x;y) between points (x1;y1) and (x2;y2)
template<typename T>
T map(T x, T x1, T x2, T y1, T y2){
    double a = (double)(y2-y1)/(double)(x2-x1);
    double b = (double)y1 - a*x1;
    return (T)(a*x+b);
}

template<typename T>
T rand_min_max(T min, T max){
    return rand() % (max-min) + min;
}

template<typename T>
T min_max(T x, T min, T max){
    return (x<min) ? min : ((x>max)? max : x);
}

// TODO : Move this class elsewhere
class LoopControler{
    public :
    unsigned long cpt = 0;
    bool first_loop = true;
    bool loop_overhead = true; // Flag : turns false if calculations are too heavy to fit in the specified frequency
    time_ms t_previous_ms = 0;
    time_us t_previous_us = 0;
    time_ms t_current_ms = millis();
    time_us t_current_us = micros();
    time_ms t_next_ms = 0;
    time_us t_next_us = 0;
    time_ms loop_duration_ms = 0;
    time_us loop_duration_us = 0;


    void start_new_frame(){
        // save last loop timestamp
        t_previous_ms = t_current_ms;
        t_previous_us = t_current_us;
        // update current loop timestamp
        t_current_us = micros();
        t_current_ms = t_current_us/1000;
        // compute next loop timestamp
        t_next_ms = t_current_ms + 1000/FRATE;
        t_next_us = t_current_us + 1000000/FRATE;

        loop_duration_ms = t_current_ms - t_previous_ms;
        loop_duration_us = t_current_us - t_previous_us;

    }


    void wait_for_next(){
        loop_overhead = false;
        while(micros() < t_next_us) {
            // std::cout << t_current_ms << " / " << micros()/1000 << " / " << t_next_ms  << std::endl;
            delayMicroseconds(100);
            loop_overhead = true;
        } // wait for the next frame

        if (first_loop) first_loop = false;
        cpt++;
    }
};

extern LoopControler frame;

/* x [as rad]*/
inline double sin_min_max(auto x, auto min, auto max){
    return (max+min)/2.0 + (max-min)/2.0 * std::sin(x);
}
inline double sin2_min_max(auto x, auto min, auto max){
    return (max+min)/2.0 + (max-min)/2.0 * std::sin(x);
}











inline void crash(){
    int i = 1/0;
}