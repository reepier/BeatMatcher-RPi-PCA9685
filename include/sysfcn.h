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
    unsigned long t_previous_ms = 0;
    unsigned long t_current_ms = millis();
    unsigned long t_next_ms = 0;
    unsigned long loop_duration_ms = 0;

    void start_new_frame(){
        t_previous_ms = t_current_ms;
        t_current_ms = millis();
        t_next_ms = t_current_ms + 1000/FRATE;

        loop_duration_ms = t_current_ms - t_previous_ms;
    }


    void wait_for_next(){
        while(micros() < 1000*t_next_ms) {
            // std::cout << t_current_ms << " / " << micros()/1000 << " / " << t_next_ms  << std::endl;
            delayMicroseconds(100); } // wait for the next frame

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